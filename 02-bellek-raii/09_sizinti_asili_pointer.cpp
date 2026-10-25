// Konu: Bellek sızıntısı, dangling pointer ve unique_ptr ile çözüm
// Ne gösteriyor: new ile alınan belleğin delete edilmemesinin sonucunu canlı nesne sayacıyla ve aynı işin unique_ptr ile otomatik yapılmasını.
// Neden önemli: RAII'nin "neden var?" sorusunun cevabı; mülakatta "bellek sızıntısını nasıl önlersin?" sorusunun temeli.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 09_sizinti_asili_pointer 09_sizinti_asili_pointer.cpp

#include <iostream>
#include <memory>   // std::unique_ptr, std::make_unique

// Kaç tane canlı nesne olduğunu sayan küçük sınıf.
// Constructor sayacı artırır, destructor azaltır (06 örneğindeki static üye).
struct Kaynak {
    inline static int canli = 0;

    Kaynak() { ++canli; }
    ~Kaynak() { --canli; }
};

// (A) SIZINTI: new ile alıyor ama hiç delete etmiyor.
void sizdir() {
    Kaynak* k = new Kaynak();
    std::cout << "  sizdir: nesne olustu (adres " << k << ")\n";
    // delete YOK: fonksiyon bitince k yok olur ama gösterdiği nesne heap'te kalır.
}

// (B) DOĞRU (elle): new ile alıp delete ile iade eden hâli.
void duzgun() {
    // TODO: sen yaz (new Kaynak ile bir nesne oluştur, adresini yazdır, sonra delete et)
    Kaynak* k = new Kaynak();
    std::cout << "  duzgun: nesne olustu (adres " << k << ")\n";
    delete k;
    k = nullptr;
}

// (C) DOĞRU (otomatik): unique_ptr, blok bitince nesneyi kendisi siler (RAII).
void otomatik() {
    // TODO: sen yaz (std::make_unique<Kaynak>() ile bir nesne oluştur; delete YAZMA)
    std::unique_ptr<Kaynak> k = std::make_unique<Kaynak>();
    std::cout << "  otomatik: nesne olustu (adres " << k.get() << ")\n";
    std::cout << "  otomatik: blok icinde canli = " << Kaynak::canli << "\n";
}

int main() {
    std::cout << "baslangic canli = " << Kaynak::canli << "\n";

    // 1) Sızıntı: 3 kez çağır.
    sizdir();
    sizdir();
    sizdir();
    // TODO: sen yaz (Kaynak::canli değerini yazdır; delete edilmeyen nesneler hâlâ yaşıyor mu?)
    std::cout << "  sizdir: canli = " << Kaynak::canli << "\n";

    // 2) Doğru kullanım: sayaç artmamalı.
    duzgun();
    // TODO: sen yaz (Kaynak::canli değerini yazdır; bu çağrıdan önce ve sonra aynı mı?)
    std::cout << "  duzgun: canli = " << Kaynak::canli << "\n";

    // 3) unique_ptr: blok bitince otomatik silinir.
    otomatik();
    // TODO: sen yaz (Kaynak::canli değerini yazdır; unique_ptr nesneyi sildi mi?)
    std::cout << "  otomatik: canli = " << Kaynak::canli << "\n";

    // 4) delete nullptr güvenli, ama aynı adrese iki kez delete güvenli değil (çalıştırma!).
    Kaynak* p = new Kaynak();
    delete p;
    p = nullptr;
    delete p;   // güvenli: nullptr'ı delete etmek hiçbir şey yapmaz
    // delete p; p = nullptr yapılmasaydı ve burada ikinci kez delete edilseydi: double free (tanımsız davranış).

    return 0;
}
