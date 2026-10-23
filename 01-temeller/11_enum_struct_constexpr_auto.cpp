// Konu: enum class, struct ile class farkı, constexpr ve auto
// Ne gösteriyor: Tip güvenli enum, varsayılan erişim farkı, derleme zamanı hesabı ve auto'nun kopya/referans tuzağını.
// Neden önemli: Modern C++ kodunda her yerde geçer; "enum ile enum class farkı" ve "const ile constexpr farkı" sık mülakat sorusudur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 11_enum_struct_constexpr_auto 11_enum_struct_constexpr_auto.cpp

#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>   // std::is_same_v
#include <vector>

// ---------------------------------------------------------------- 1) enum ve enum class
// Eski tip enum: isimler dış kapsama sızar ve int'e kendiliğinden dönüşür.
enum Renk { KIRMIZI, YESIL, MAVI };
// enum Isik { KIRMIZI };   // HATA olurdu: KIRMIZI ismi zaten Renk tarafından kullanılıyor (isim çakışması)

// enum class: isimler kendi kapsamında kalır (Durum::Bekle), int'e kendiliğinden dönüşmez.
// ": uint8_t" ile altındaki tipi (boyutu) kendimiz seçiyoruz: tek bayt.
enum class Durum : uint8_t { Bekle = 0, Ucus = 1, Inis = 2 };

std::string durumAdi(Durum d) {
    switch (d) {
        case Durum::Bekle: return "Bekle";
        case Durum::Ucus:  return "Ucus";
        case Durum::Inis:  return "Inis";
    }
    return "Bilinmiyor";
}

// ---------------------------------------------------------------- 2) struct ve class
// struct: varsayılan erişim PUBLIC. Basit veri taşımak için kullanılır.
struct Olcum {
    int id;
    double deger;
};

// class: varsayılan erişim PRIVATE. Veriyi saklayıp erişimi kontrol eder (encapsulation).
class Batarya {
    double voltaj_;   // dışarıdan doğrudan erişilemez
public:
    explicit Batarya(double v) : voltaj_(v) {}
    double voltaj() const { return voltaj_; }
    bool dusukMu() const { return voltaj_ < 3.5; }
};

// ---------------------------------------------------------------- 3) constexpr
// Derleme zamanında hesaplanabilen fonksiyon.
constexpr int kare(int x) { return x * x; }

constexpr unsigned long long faktoriyel(unsigned n) {
    return n <= 1 ? 1ULL : n * faktoriyel(n - 1);
}

constexpr int BOYUT = kare(4);   // 16, derleme zamanında hesaplanır
static_assert(BOYUT == 16, "kare(4) 16 olmali");
static_assert(faktoriyel(5) == 120, "5! = 120 olmali");

int main() {
    // ------------------------------------------------------------ 1) enum
    std::cout << "--- 1) enum ve enum class ---\n";
    int r = YESIL;                    // eski enum: int'e kendiliğinden dönüşür
    std::cout << "YESIL (eski enum) int olarak = " << r << "\n";
    std::cout << "KIRMIZI == 0 ? " << (KIRMIZI == 0) << "\n";

    Durum d = Durum::Ucus;
    // int x = d;                     // HATA: enum class int'e kendiliğinden dönüşmez
    int x = static_cast<int>(d);      // dönüşüm açıkça yazılmalı
    std::cout << "Durum::Ucus int olarak = " << x << "\n";
    std::cout << "durumAdi = " << durumAdi(d) << "\n";
    std::cout << "sizeof(Durum) = " << sizeof(Durum) << " bayt, sizeof(Renk) = " << sizeof(Renk) << " bayt\n";

    // ------------------------------------------------------------ 2) struct / class
    std::cout << "\n--- 2) struct ve class ---\n";
    Olcum o{1, 23.5};                 // struct: üyelere doğrudan erişim
    o.deger += 1.0;
    std::cout << "Olcum: id=" << o.id << " deger=" << o.deger << "\n";

    Batarya b(3.2);
    // b.voltaj_ = 4.0;               // HATA: voltaj_ private
    std::cout << "Batarya voltaj = " << b.voltaj() << ", dusuk mu? " << b.dusukMu() << "\n";

    // ------------------------------------------------------------ 3) constexpr
    std::cout << "\n--- 3) constexpr ---\n";
    int dizi[BOYUT];                  // dizi boyutu sabit ifade olmak zorunda: constexpr burada işe yarar
    std::cout << "dizi eleman sayisi = " << sizeof(dizi) / sizeof(dizi[0]) << "\n";
    std::cout << "faktoriyel(10) = " << faktoriyel(10) << "\n";

    int girdi = 7;                    // çalışma zamanında belli olan değer
    const int sabitAmaCalismaZamani = girdi * 2;   // const ama derleme zamanı sabiti DEĞİL
    std::cout << "kare(girdi) = " << kare(girdi) << "  (constexpr fonksiyon calisma zamaninda da kullanilabilir)\n";
    std::cout << "const (calisma zamani) = " << sabitAmaCalismaZamani << "\n";
    // int dizi2[sabitAmaCalismaZamani];   // standart C++'ta HATA: sabit ifade değil

    // ------------------------------------------------------------ 4) auto
    std::cout << "\n--- 4) auto ---\n";
    auto i = 5;           // int
    auto dbl = 3.14;      // double
    auto f = 2.5f;        // float
    auto s = "merhaba";   // const char* (std::string DEĞİL)
    static_assert(std::is_same_v<decltype(i), int>, "i int olmali");
    static_assert(std::is_same_v<decltype(dbl), double>, "dbl double olmali");
    static_assert(std::is_same_v<decltype(f), float>, "f float olmali");
    static_assert(std::is_same_v<decltype(s), const char*>, "s const char* olmali");
    std::cout << "auto tipleri derleme zamaninda dogrulandi (static_assert gecti)\n";

    std::vector<int> v{10, 20, 30};
    int toplam = 0;
    for (const auto& e : v) {         // const auto&: kopya yok, değiştirmek de yok
        toplam += e;
    }
    std::cout << "vector toplami = " << toplam << "\n";

    // auto tuzağı: auto, const ve referansı atar; kopya üretir.
    int orijinal = 10;
    int& ref = orijinal;
    auto kopya = ref;                 // int (KOPYA)
    auto& takma = ref;                // int& (takma ad)
    kopya = 99;
    std::cout << "kopya = 99 sonrasi: kopya = " << kopya << ", orijinal = " << orijinal << "\n";
    takma = 50;
    std::cout << "takma = 50 sonrasi orijinal = " << orijinal << "\n";

    return 0;
}
