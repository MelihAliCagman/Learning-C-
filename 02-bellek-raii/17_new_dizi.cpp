// Konu: new[] / delete[]: heap'te dizi, nesne dizisi ve modern alternatifler
// Ne gösteriyor: Dinamik dizinin oluşturulup silinmesini, nesne dizisinde constructor/destructor sayısını, new başarısızlığını ve vector/unique_ptr<T[]>.
// Neden önemli: "delete ile delete[] farkı" klasik mülakat sorusudur; yanlış eşleştirme tanımsız davranıştır.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 17_new_dizi 17_new_dizi.cpp

#include <cstddef>
#include <iostream>
#include <memory>
#include <new>      // std::nothrow, std::bad_alloc
#include <vector>

// Her nesnenin oluşumunu/yok oluşunu sayar (09 örneğindeki gibi).
struct Kaynak {
    inline static int canli = 0;

    Kaynak() { ++canli; }
    ~Kaynak() { --canli; }
};

int main() {
    // ------------------------------------------------------------ 1) Temel kullanım
    std::cout << "--- 1) new[] ve delete[] ---\n";
    int n = 5;
    int* a = new int[n];            // n eleman, DEGERLERI BELIRSIZ (cop)
    for (int i = 0; i < n; ++i) {
        a[i] = i * 10;
    }
    std::cout << "a: ";
    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
    delete[] a;                     // dizi icin delete[] (delete DEGIL)
    a = nullptr;

    // ------------------------------------------------------------ 2) Sıfırlanmış başlatma
    int* z = new int[4]();          // () ile hepsi 0
    std::cout << "new int[4]() : " << z[0] << " " << z[1] << " " << z[2] << " " << z[3] << "\n";
    delete[] z;

    // ------------------------------------------------------------ 3) Nesne dizisi: constructor ve destructor sayisi
    std::cout << "\n--- 2) Nesne dizisi ---\n";
    std::cout << "baslangic canli = " << Kaynak::canli << "\n";
    Kaynak* k = new Kaynak[3];      // 3 constructor
    std::cout << "new Kaynak[3] sonrasi canli = " << Kaynak::canli << "\n";
    delete[] k;                     // 3 destructor
    k = nullptr;
    std::cout << "delete[] sonrasi canli = " << Kaynak::canli << "\n";
    // delete k;  // YANLIS: tek destructor calisir, 2 nesne sizar, ustelik tanimsiz davranis (asagidaki notlara bak)

    // ------------------------------------------------------------ 4) Boyut bilgisi kaybolur
    std::cout << "\n--- 3) Boyut ---\n";
    int* p = new int[100];
    std::cout << "sizeof(p) = " << sizeof(p) << " (100 elemanli diziye degil, sadece pointer'a bakiyor)\n";
    delete[] p;

    // ------------------------------------------------------------ 5) Başarısızlık
    std::cout << "\n--- 4) new basarisiz olursa ---\n";
    std::size_t cokBuyuk = static_cast<std::size_t>(1) << 45;   // 2^45 eleman: bellekte yer yok
    try {
        int* dev = new int[cokBuyuk];
        std::cout << "beklenmedik: tahsis edildi\n";
        delete[] dev;
    } catch (const std::bad_alloc&) {
        std::cout << "new -> std::bad_alloc istisnasi (varsayilan davranis)\n";
    }
    int* yok = new (std::nothrow) int[cokBuyuk];   // nothrow: istisna yerine nullptr
    std::cout << "new (std::nothrow) -> " << (yok == nullptr ? "nullptr dondu" : "tahsis edildi") << "\n";
    delete[] yok;   // nullptr'i delete[] etmek guvenli

    // ------------------------------------------------------------ 6) Modern alternatifler
    std::cout << "\n--- 5) Modern alternatifler ---\n";
    std::vector<int> v(5, 7);                         // vector: boyut bilir, kendi kendini siler
    std::cout << "vector size = " << v.size() << ", v[2] = " << v[2] << "\n";

    std::unique_ptr<int[]> u = std::make_unique<int[]>(4);   // 0 ile baslatir, delete[] otomatik
    u[2] = 42;
    std::cout << "unique_ptr<int[]>: u[0] = " << u[0] << ", u[2] = " << u[2] << "\n";

    {
        std::unique_ptr<Kaynak[]> ku(new Kaynak[2]);
        std::cout << "unique_ptr<Kaynak[]> blok icinde canli = " << Kaynak::canli << "\n";
    }
    std::cout << "blok bitti, canli = " << Kaynak::canli << "  (delete[] otomatik cagrildi)\n";

    return 0;
}
