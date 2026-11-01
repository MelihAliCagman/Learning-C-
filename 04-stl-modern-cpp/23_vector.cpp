// Konu: std::vector: size/capacity, yeniden tahsis (reallocation), iterator geçersizleşmesi, erase-remove ve emplace_back
// Ne gösteriyor: Kapasitenin nasıl büyüdüğünü, reserve'ün neden hızlandırdığını, bellek adresinin değişmesini (geçersizleşme), elemanları güvenle silmeyi.
// Neden önemli: STL mülakatının en sık sorulan konusu: "size ile capacity farkı, vector büyürken ne olur, iterator ne zaman geçersizleşir?"
// Derleme: g++ -std=c++17 -Wall -Wextra -o 23_vector 23_vector.cpp

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

void yaz(const char* etiket, const std::vector<int>& v) {
    std::cout << etiket;
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

// emplace_back / push_back farkını görmek için kopya-taşıma sayan küçük sınıf.
struct Sayac {
    inline static int olusum = 0;
    inline static int tasima = 0;
    int deger;
    explicit Sayac(int d) : deger(d) { ++olusum; }
    Sayac(Sayac&& diger) noexcept : deger(diger.deger) { ++tasima; }
    Sayac(const Sayac& diger) = default;
};

int main() {
    // ------------------------------------------------------------ 1) size ve capacity
    std::cout << "--- 1) size ve capacity: kapasite nasil buyur? ---\n";
    std::vector<int> v;
    std::size_t sonKapasite = v.capacity();
    std::cout << "  baslangic: size = " << v.size() << ", capacity = " << v.capacity() << ", sizeof(vector) = " << sizeof(v) << "\n";
    for (int i = 1; i <= 20; ++i) {
        v.push_back(i);
        if (v.capacity() != sonKapasite) {
            sonKapasite = v.capacity();
            std::cout << "  " << i << ". eleman eklendi: yeni capacity = " << sonKapasite << "  (yeniden tahsis oldu)\n";
        }
    }

    // ------------------------------------------------------------ 2) reserve: yeniden tahsisi önler
    std::cout << "\n--- 2) reserve: kac kez yeniden tahsis? ---\n";
    auto tahsisSay = [](bool ayir) {
        std::vector<int> a;
        if (ayir) {
            a.reserve(1000);
        }
        int sayac = 0;
        const int* onceki = a.data();
        for (int i = 0; i < 1000; ++i) {
            a.push_back(i);
            if (a.data() != onceki) {             // bellek adresi değiştiyse yeniden tahsis olmuştur
                ++sayac;
                onceki = a.data();
            }
        }
        return sayac;
    };
    std::cout << "  1000 push_back, reserve YOK : " << tahsisSay(false) << " yeniden tahsis\n";
    std::cout << "  1000 push_back, reserve(1000): " << tahsisSay(true) << " yeniden tahsis\n";

    // ------------------------------------------------------------ 3) Geçersizleşme: adres değişir
    std::cout << "\n--- 3) iterator/pointer gecersizlesmesi ---\n";
    std::vector<int> g = {1, 2, 3};
    g.shrink_to_fit();                              // kapasiteyi boyuta eşitle (3)
    std::uintptr_t eskiAdres = reinterpret_cast<std::uintptr_t>(g.data());
    std::cout << "  capacity = " << g.capacity() << " (dolu), push_back oncesi adres kaydedildi\n";
    g.push_back(4);                                 // kapasite doluydu: yeni belleğe taşındı
    std::uintptr_t yeniAdres = reinterpret_cast<std::uintptr_t>(g.data());
    std::cout << "  push_back sonrasi adres degisti mi? " << (eskiAdres != yeniAdres)
              << "  -> eski iterator/pointer/referans artik GECERSIZ (kullanmak tanimsiz davranis)\n";
    std::cout << "  not: kapasite yetiyorsa (reserve sonrasi) adres degismez, ama insert/erase yine kaydirir.\n";

    // ------------------------------------------------------------ 4) Silme: erase ve erase-remove
    std::cout << "\n--- 4) silme ---\n";
    std::vector<int> s = {1, 2, 3, 4, 5, 6, 7, 8};
    yaz("  once            : ", s);
    s.erase(std::remove_if(s.begin(), s.end(), [](int x) { return x % 2 == 0; }), s.end());   // erase-remove: tek geçiş, O(n)
    yaz("  ciftler silindi : ", s);
    for (auto it = s.begin(); it != s.end();) {      // döngüde silerken: erase yeni geçerli iterator döndürür
        if (*it == 5) {
            it = s.erase(it);
        } else {
            ++it;
        }
    }
    yaz("  5 silindi       : ", s);
    s.clear();
    std::cout << "  clear sonrasi: size = " << s.size() << ", capacity = " << s.capacity() << "  (clear kapasiteyi SERBEST BIRAKMAZ)\n";
    s.shrink_to_fit();
    std::cout << "  shrink_to_fit sonrasi: capacity = " << s.capacity() << "\n";

    // ------------------------------------------------------------ 5) Constructor tuzağı
    std::cout << "\n--- 5) vector<int>(5, 7) ile vector<int>{5, 7} ---\n";
    std::vector<int> parantez(5, 7);                // 5 tane 7
    std::vector<int> suslu{5, 7};                   // 2 elemanlı: 5 ve 7
    yaz("  (5, 7) : ", parantez);
    yaz("  {5, 7} : ", suslu);

    // ------------------------------------------------------------ 6) at() ve []
    std::cout << "\n--- 6) at() ile [] ---\n";
    std::vector<int> k = {10, 20, 30};
    std::cout << "  k[1] = " << k[1] << ", k.at(1) = " << k.at(1) << "\n";
    try {
        std::cout << k.at(10) << "\n";
    } catch (const std::out_of_range&) {
        std::cout << "  k.at(10) -> out_of_range istisnasi (k[10] sinir kontrolu yapmaz: tanimsiz davranis)\n";
    }

    // ------------------------------------------------------------ 7) emplace_back ve push_back
    std::cout << "\n--- 7) push_back ve emplace_back ---\n";
    {
        std::vector<Sayac> a;
        a.reserve(4);                               // yeniden tahsis karışmasın
        Sayac::olusum = 0;
        Sayac::tasima = 0;
        a.push_back(Sayac(1));                      // geçici nesne oluştur + vector'e TAŞI
        std::cout << "  push_back(Sayac(1)) : olusum = " << Sayac::olusum << ", tasima = " << Sayac::tasima << "\n";
        Sayac::olusum = 0;
        Sayac::tasima = 0;
        a.emplace_back(2);                          // doğrudan vector içinde oluştur
        std::cout << "  emplace_back(2)     : olusum = " << Sayac::olusum << ", tasima = " << Sayac::tasima << "\n";
    }
    return 0;
}
