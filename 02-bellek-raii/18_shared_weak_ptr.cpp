// Konu: shared_ptr, weak_ptr ve döngüsel referans (circular reference)
// Ne gösteriyor: Paylaşımlı sahipliği (use_count), weak_ptr'ın sahiplenmeden gözlemesini ve iki shared_ptr'ın birbirini tutarak sızıntı yapmasını.
// Neden önemli: "unique_ptr ile shared_ptr farkı" ve "weak_ptr neden var?" mülakatta çok sorulur; ROS 2'de de shared_ptr her yerde geçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 18_shared_weak_ptr 18_shared_weak_ptr.cpp

#include <iostream>
#include <memory>
#include <string>

struct Kaynak {
    inline static int canli = 0;
    std::string ad;

    explicit Kaynak(std::string a) : ad(std::move(a)) {
        ++canli;
        std::cout << "    [" << ad << " olustu]\n";
    }
    ~Kaynak() {
        --canli;
        std::cout << "    [" << ad << " yok oldu]\n";
    }
};

// Sahiplik paylaşmayan fonksiyon: kopya ALMA (use_count artar), const referans ya da ham pointer al.
void degerleAl(std::shared_ptr<Kaynak> p) {
    std::cout << "  degerleAl icinde use_count = " << p.use_count() << "  (kopya: sayac artti)\n";
}
void referansla(const std::shared_ptr<Kaynak>& p) {
    std::cout << "  referansla icinde use_count = " << p.use_count() << "  (kopya yok)\n";
}

// ---------------------------------------------------------------- Döngüsel referans
struct DugumKotu {          // iki taraf da shared_ptr: SIZINTI
    inline static int canli = 0;
    std::shared_ptr<DugumKotu> diger;
    DugumKotu() { ++canli; }
    ~DugumKotu() { --canli; }
};

struct DugumIyi {           // geri bağlantı weak_ptr: sızıntı yok
    inline static int canli = 0;
    std::shared_ptr<DugumIyi> sonraki;
    std::weak_ptr<DugumIyi> onceki;
    DugumIyi() { ++canli; }
    ~DugumIyi() { --canli; }
};

int main() {
    // ------------------------------------------------------------ 1) shared_ptr ve sayaç
    std::cout << "--- 1) shared_ptr: paylasimli sahiplik ---\n";
    std::shared_ptr<Kaynak> a = std::make_shared<Kaynak>("A");
    std::cout << "a olustu: use_count = " << a.use_count() << "\n";
    {
        std::shared_ptr<Kaynak> b = a;       // kopya: ayni nesneyi paylasir
        std::shared_ptr<Kaynak> c = a;
        std::cout << "b ve c kopyalandi: use_count = " << a.use_count() << "\n";
    }
    std::cout << "blok bitti: use_count = " << a.use_count() << "  (b ve c yok oldu, nesne yasiyor)\n";
    degerleAl(a);
    referansla(a);
    std::cout << "son use_count = " << a.use_count() << "\n";
    a.reset();                               // son sahip birakti: nesne silinir
    std::cout << "reset sonrasi canli = " << Kaynak::canli << "\n";

    // ------------------------------------------------------------ 2) unique_ptr'dan shared_ptr'a
    std::cout << "\n--- 2) unique_ptr -> shared_ptr ---\n";
    std::unique_ptr<Kaynak> u = std::make_unique<Kaynak>("U");
    std::shared_ptr<Kaynak> s = std::move(u);   // sahiplik devredildi
    std::cout << "tasimadan sonra u " << (u == nullptr ? "null" : "dolu") << ", s.use_count = " << s.use_count() << "\n";
    s.reset();

    // ------------------------------------------------------------ 3) weak_ptr
    std::cout << "\n--- 3) weak_ptr: sahiplenmeden gozlemek ---\n";
    std::weak_ptr<Kaynak> w;
    {
        std::shared_ptr<Kaynak> g = std::make_shared<Kaynak>("B");
        w = g;                                // weak_ptr sayaci ARTIRMAZ
        std::cout << "w = g: use_count = " << g.use_count() << ", w.expired() = " << w.expired() << "\n";
        if (std::shared_ptr<Kaynak> gecici = w.lock()) {   // lock(): nesne yasiyorsa shared_ptr verir
            std::cout << "w.lock() basarili: " << gecici->ad << ", use_count = " << g.use_count() << "\n";
        }
    }
    std::cout << "blok bitti: w.expired() = " << w.expired() << "\n";
    std::cout << "w.lock() == nullptr ? " << (w.lock() == nullptr) << "\n";

    // ------------------------------------------------------------ 4) Döngüsel referans: sızıntı
    std::cout << "\n--- 4) Dongusel referans (iki shared_ptr) ---\n";
    {
        std::shared_ptr<DugumKotu> x = std::make_shared<DugumKotu>();
        std::shared_ptr<DugumKotu> y = std::make_shared<DugumKotu>();
        x->diger = y;
        y->diger = x;
        std::cout << "x.use_count = " << x.use_count() << ", y.use_count = " << y.use_count() << "\n";
    }
    std::cout << "blok bitti: canli DugumKotu = " << DugumKotu::canli << "  (SIZINTI: birbirini tutuyorlar)\n";

    std::cout << "\n--- 5) Ayni yapi, geri baglanti weak_ptr ---\n";
    {
        std::shared_ptr<DugumIyi> x = std::make_shared<DugumIyi>();
        std::shared_ptr<DugumIyi> y = std::make_shared<DugumIyi>();
        x->sonraki = y;       // ileri: shared (sahiplik)
        y->onceki = x;        // geri : weak   (sahiplik yok)
        std::cout << "x.use_count = " << x.use_count() << ", y.use_count = " << y.use_count() << "\n";
    }
    std::cout << "blok bitti: canli DugumIyi = " << DugumIyi::canli << "  (sizinti yok)\n";

    // ------------------------------------------------------------ 6) Boyut
    std::cout << "\n--- 6) Boyutlar ---\n";
    std::cout << "sizeof(unique_ptr) = " << sizeof(std::unique_ptr<int>) << ", sizeof(shared_ptr) = "
              << sizeof(std::shared_ptr<int>) << ", sizeof(weak_ptr) = " << sizeof(std::weak_ptr<int>) << "\n";

    return 0;
}
