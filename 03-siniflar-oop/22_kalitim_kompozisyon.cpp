// Konu: Kalıtım (is-a) ile kompozisyon (has-a), erişim belirleyicileri, oluşum sırası ve elmas (diamond) problemi
// Ne gösteriyor: Taban sınıfın önce, parçaların tanımlanma sırasıyla oluşmasını; neden "kalıtımdan çok kompozisyon" denildiğini; çalışma zamanında değiştirilebilen davranışı; çoklu kalıtımda elmas sorununu.
// Neden önemli: "Kalıtım mı kompozisyon mu?" OOP mülakatlarında neredeyse her zaman sorulur; tasarım olgunluğunu ölçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 22_kalitim_kompozisyon 22_kalitim_kompozisyon.cpp

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// ================================================================ A) KALITIM (is-a): "Drone bir Arac'tır"
class Arac {
protected:                                   // türemiş sınıflar erişir, dışarısı erişemez
    std::string ad_;

public:
    explicit Arac(std::string ad) : ad_(std::move(ad)) { std::cout << "  [Arac ctor]  " << ad_ << "\n"; }
    virtual ~Arac() { std::cout << "  [Arac dtor]  " << ad_ << "\n"; }
    virtual void bilgi() const { std::cout << "  Arac: " << ad_ << "\n"; }
};

class Drone : public Arac {
    double menzil_;

public:
    // Taban sınıf constructor'ı initializer list'te çağrılır; taban ÖNCE oluşur.
    Drone(std::string ad, double menzil) : Arac(std::move(ad)), menzil_(menzil) {
        std::cout << "  [Drone ctor] " << ad_ << "\n";
    }
    ~Drone() override { std::cout << "  [Drone dtor] " << ad_ << "\n"; }
    void bilgi() const override {
        std::cout << "  Drone: " << ad_ << ", menzil " << menzil_ << " km\n";   // protected ad_'ye erişebilir
    }
};

// ================================================================ B) KOMPOZİSYON (has-a): "IHA'nın pili ve motoru VAR"
class Pil {
public:
    Pil() { std::cout << "  [Pil ctor]\n"; }
    ~Pil() { std::cout << "  [Pil dtor]\n"; }
};

class Motor {
public:
    Motor() { std::cout << "  [Motor ctor]\n"; }
    ~Motor() { std::cout << "  [Motor dtor]\n"; }
};

class IHA {
    Motor motor_;                            // üyeler TANIMLANMA sırasıyla oluşur: önce motor_, sonra pil_
    Pil pil_;

public:
    IHA() { std::cout << "  [IHA ctor]\n"; }
    ~IHA() { std::cout << "  [IHA dtor]\n"; }        // yok oluş TERS sırada: önce gövde, sonra pil_, sonra motor_
};

// ================================================================ C) Neden "kalıtımdan çok kompozisyon"?
// KÖTÜ: Yığın "vector'dür" demek, vector'ün TÜM arayüzünü (insert, erase, ...) dışarı açar ve yığın kuralını bozar.
class YiginKotu : public std::vector<int> {
public:
    void it(int x) { push_back(x); }
};

// İYİ: Yığının vector'ü VAR; yalnızca istediğimiz işlemleri açarız (encapsulation).
class Yigin {
    std::vector<int> v_;

public:
    void it(int x) { v_.push_back(x); }
    bool cek(int& x) {
        if (v_.empty()) {
            return false;
        }
        x = v_.back();
        v_.pop_back();
        return true;
    }
    bool bosMu() const { return v_.empty(); }
};

// ================================================================ D) Kompozisyon + çok biçimlilik: davranışı çalışma zamanında değiştir
class UcusModu {
public:
    virtual ~UcusModu() = default;
    virtual double hiz() const = 0;
};
class SakinMod : public UcusModu {
public:
    double hiz() const override { return 10.0; }
};
class HizliMod : public UcusModu {
public:
    double hiz() const override { return 25.0; }
};

class Drone2 {
    std::unique_ptr<UcusModu> mod_;          // "has-a": bir uçuş modu var, istediğimiz zaman değiştirebiliriz

public:
    explicit Drone2(std::unique_ptr<UcusModu> mod) : mod_(std::move(mod)) {}
    void modDegistir(std::unique_ptr<UcusModu> yeni) { mod_ = std::move(yeni); }
    double hiz() const { return mod_->hiz(); }
};

// ================================================================ E) Çoklu kalıtım ve elmas (diamond) problemi
struct Cihaz {
    inline static int adet = 0;              // kaç Cihaz alt nesnesi oluştu
    int id = 0;
    Cihaz() { ++adet; }
};
struct Kamera : Cihaz {};
struct Gps : Cihaz {};
struct SensorKutusu : Kamera, Gps {};        // İKİ AYRI Cihaz alt nesnesi içerir

struct CihazV {
    inline static int adet = 0;
    int id = 0;
    CihazV() { ++adet; }
};
struct KameraV : virtual CihazV {};          // virtual kalıtım: ortak taban TEK kopya
struct GpsV : virtual CihazV {};
struct SensorKutusuV : KameraV, GpsV {};

int main() {
    std::cout << "--- A) Kalitim: olusum ve yok olus sirasi ---\n";
    {
        Drone d("D1", 5.5);
        d.bilgi();
        Arac* p = &d;
        p->bilgi();                          // sanal fonksiyon: Drone sürümü çalışır
    }

    std::cout << "\n--- B) Kompozisyon: uyelerin sirasi ---\n";
    {
        IHA iha;
    }

    std::cout << "\n--- C) Neden kompozisyon? ---\n";
    YiginKotu kotu;
    kotu.it(1);
    kotu.it(2);
    kotu.insert(kotu.begin(), 99);           // vector arayüzü açık: yığının ALTINA eleman eklenebiliyor (yığın kuralı bozuldu)
    std::cout << "  YiginKotu icerik: ";
    for (int x : kotu) {
        std::cout << x << " ";
    }
    std::cout << "(99 yiginin altina girdi!)\n";

    Yigin iyi;
    iyi.it(1);
    iyi.it(2);
    int x = 0;
    iyi.cek(x);
    std::cout << "  Yigin (kompozisyon): cekilen = " << x << "  (insert yok, sadece it/cek)\n";

    std::cout << "\n--- D) Kompozisyon + cok bicimlilik ---\n";
    Drone2 drone(std::make_unique<SakinMod>());
    std::cout << "  sakin mod hizi = " << drone.hiz() << "\n";
    drone.modDegistir(std::make_unique<HizliMod>());   // çalışma zamanında davranış değişti
    std::cout << "  hizli mod hizi = " << drone.hiz() << "\n";

    std::cout << "\n--- E) Elmas problemi ---\n";
    SensorKutusu s;
    std::cout << "  normal kalitim: Cihaz alt nesne sayisi = " << Cihaz::adet << "  (IKI kopya)\n";
    s.Kamera::id = 1;
    s.Gps::id = 2;
    std::cout << "  s.Kamera::id = " << s.Kamera::id << ", s.Gps::id = " << s.Gps::id << "  (ayri id'ler; s.id yazmak BELIRSIZ olurdu)\n";
    SensorKutusuV sv;
    sv.id = 5;                                          // virtual kalıtımda tek kopya: belirsizlik yok
    std::cout << "  virtual kalitim: CihazV alt nesne sayisi = " << CihazV::adet << "  (TEK kopya), sv.id = " << sv.id << "\n";

    std::cout << "\n--- main sonu ---\n";
    return 0;
}
