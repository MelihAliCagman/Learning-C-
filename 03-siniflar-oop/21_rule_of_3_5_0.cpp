// Konu: Kopyalama ve taşıma (copy / move) ve Rule of 3 / 5 / 0
// Ne gösteriyor: Heap belleği yöneten bir sınıfta derin kopya, taşıma (kaynağı çalmak), özel üye fonksiyonların hangisinin ne zaman çağrıldığını; Rule of 0 ve noexcept'in vector üzerindeki etkisini.
// Neden önemli: OOP mülakatının en derin sorusu: "Rule of 3/5/0 nedir, neden gerekir, taşıma neden noexcept olmalı?"
// Derleme: g++ -std=c++17 -Wall -Wextra -o 21_rule_of_3_5_0 21_rule_of_3_5_0.cpp

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------- 1) Rule of 5: ham pointer ile heap'te dizi yöneten sınıf
// Rule of 3: destructor, kopya constructor ve kopya atamadan birini yazdıysan ÜÇÜNÜ de yaz.
// Rule of 5: bunlara taşıma constructor ve taşıma atamayı ekle.
class Tampon {
    std::string ad_;
    int* veri_;
    std::size_t boyut_;

    void degistir(Tampon& diger) noexcept {
        std::swap(veri_, diger.veri_);
        std::swap(boyut_, diger.boyut_);
    }

public:
    Tampon(const std::string& ad, std::size_t boyut)
        : ad_(ad), veri_(boyut > 0 ? new int[boyut]() : nullptr), boyut_(boyut) {
        std::cout << "  [ctor        " << ad_ << "] boyut = " << boyut_ << "\n";
    }

    // (1) Destructor: kaynağı geri verir.
    ~Tampon() {
        std::cout << "  [dtor        " << ad_ << "]\n";
        delete[] veri_;
    }

    // (2) Kopya constructor: DERİN kopya (yeni bellek ayırıp içeriği kopyalar).
    Tampon(const Tampon& diger)
        : ad_(diger.ad_ + "'"), veri_(diger.boyut_ > 0 ? new int[diger.boyut_] : nullptr), boyut_(diger.boyut_) {
        std::copy(diger.veri_, diger.veri_ + boyut_, veri_);
        std::cout << "  [KOPYA ctor  " << ad_ << "] " << diger.ad_ << "'den kopyalandi\n";
    }

    // (3) Kopya atama: copy-and-swap. Önce geçici bir kopya yap, sonra içeriğini takas et (istisna güvenli, kendine atama güvenli).
    Tampon& operator=(const Tampon& diger) {
        std::cout << "  [KOPYA atama " << ad_ << "] <- " << diger.ad_ << "\n";
        if (this != &diger) {
            Tampon gecici(diger);
            degistir(gecici);          // eski içerik geçici'ye gider, geçici yok olurken serbest bırakılır
        }
        return *this;
    }

    // (4) Taşıma constructor: kaynağı ÇALAR (kopyalamaz), kaynağı boş bırakır. noexcept ÖNEMLİ.
    Tampon(Tampon&& diger) noexcept : ad_(std::move(diger.ad_)), veri_(diger.veri_), boyut_(diger.boyut_) {
        diger.veri_ = nullptr;
        diger.boyut_ = 0;
        std::cout << "  [TASIMA ctor " << ad_ << "] kaynak calindi\n";
    }

    // (5) Taşıma atama.
    Tampon& operator=(Tampon&& diger) noexcept {
        std::cout << "  [TASIMA atama " << ad_ << "] <- " << diger.ad_ << "\n";
        if (this != &diger) {
            delete[] veri_;            // kendi eski kaynağını bırak
            veri_ = diger.veri_;
            boyut_ = diger.boyut_;
            diger.veri_ = nullptr;
            diger.boyut_ = 0;
        }
        return *this;
    }

    int& operator[](std::size_t i) { return veri_[i]; }
    std::size_t boyut() const { return boyut_; }
};

Tampon uret() {
    Tampon t("uretilen", 4);
    return t;                          // kopya YOK: derleyici ya taşır ya da hiç taşımadan doğrudan çağıranın nesnesini kurar (elision)
}

// ---------------------------------------------------------------- 2) Rule of 0: kaynağı hazır RAII sınıflarına bırak
// Üyeler vector ve string olduğu için derleyicinin ürettiği kopyalama/taşıma/destructor DOĞRU çalışır: hiçbirini yazma.
struct Oto {
    std::string ad;
    std::vector<int> veri;
};

// ---------------------------------------------------------------- 3) noexcept taşıma ve vector büyümesi
// vector büyürken elemanları yeni belleğe taşır. Taşıma noexcept DEĞİLSE (istisna fırlatabilir), güvenlik için KOPYALAR.
struct Hizli {
    inline static int kopya = 0;
    inline static int tasima = 0;
    Hizli() = default;
    Hizli(const Hizli&) { ++kopya; }
    Hizli(Hizli&&) noexcept { ++tasima; }
};

struct Yavas {
    inline static int kopya = 0;
    inline static int tasima = 0;
    Yavas() = default;
    Yavas(const Yavas&) { ++kopya; }
    Yavas(Yavas&&) { ++tasima; }       // noexcept YOK
};

template <typename T>
void dene(const char* ad) {
    T::kopya = 0;
    T::tasima = 0;
    std::vector<T> v;
    for (int i = 0; i < 8; ++i) {
        v.emplace_back();              // kapasite büyürken mevcut elemanlar yeni belleğe aktarılır
    }
    std::cout << "  " << ad << ": kopya = " << T::kopya << ", tasima = " << T::tasima << "\n";
}

int main() {
    std::cout << "--- 1) Kopyalama (derin kopya) ---\n";
    Tampon a("a", 3);
    a[0] = 7;
    Tampon b = a;                      // kopya constructor
    b[0] = 99;                         // b'yi değiştir
    std::cout << "  a[0] = " << a[0] << ", b[0] = " << b[0] << "  (bagimsiz: derin kopya)\n";
    Tampon c("c", 2);
    c = a;                             // kopya atama

    std::cout << "\n--- 2) Tasima ---\n";
    Tampon d = std::move(a);           // taşıma constructor: a'nın kaynağı d'ye geçer
    std::cout << "  tasimadan sonra a.boyut() = " << a.boyut() << ", d.boyut() = " << d.boyut() << "\n";
    Tampon e("e", 1);
    e = std::move(b);                  // taşıma atama
    std::cout << "  tasimadan sonra b.boyut() = " << b.boyut() << ", e.boyut() = " << e.boyut() << "\n";

    std::cout << "\n--- 3) Fonksiyondan donme ---\n";
    Tampon f = uret();
    std::cout << "  f.boyut() = " << f.boyut() << "\n";

    std::cout << "\n--- 4) Rule of 0 ---\n";
    Oto o1{"oto1", {1, 2, 3}};
    Oto o2 = o1;                       // derleyicinin kopyası: vector ve string derin kopyalanır
    o2.veri[0] = 100;
    Oto o3 = std::move(o1);            // derleyicinin taşıması: o1'in vector'ü o3'e geçer
    std::cout << "  o1.veri[0] = ?   o2.veri[0] = " << o2.veri[0] << ", o3.veri[0] = " << o3.veri[0]
              << ", tasima sonrasi o1.veri.size() = " << o1.veri.size() << "\n";

    std::cout << "\n--- 5) noexcept tasima ve vector buyumesi (8 emplace_back) ---\n";
    dene<Hizli>("noexcept tasima  ");
    dene<Yavas>("noexcept YOK     ");

    std::cout << "\n--- main sonu: nesneler tersten yok olur ---\n";
    return 0;
}
