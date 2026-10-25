// Konu: virtual, override, soyut sınıf (pure virtual) ve sanal destructor
// Ne gösteriyor: Taban sınıf pointer'ı ile türemiş sınıfın doğru fonksiyonunu çağırmayı (çok biçimlilik), dilimlemeyi ve sanal destructor'ın neden gerekli olduğunu.
// Neden önemli: OOP mülakatının en sık sorulan konusu: "virtual nedir, nasıl çalışır, sanal destructor neden gerekli, override ne işe yarar?"
// Derleme: g++ -std=c++17 -Wall -Wextra -o 20_virtual 20_virtual.cpp

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ---------------------------------------------------------------- 1) Sanal olmayan ve sanal fonksiyon
struct A {
    std::string kimim() const { return "A::kimim   (sanal DEGIL)"; }
    virtual std::string kimimV() const { return "A::kimimV  (sanal)"; }
    virtual ~A() = default;
};

struct B : A {
    std::string kimim() const { return "B::kimim   (sanal DEGIL)"; }   // taban sürümünü GİZLER, override değil
    std::string kimimV() const override { return "B::kimimV  (sanal)"; }
};

// ---------------------------------------------------------------- 2) Soyut sınıf ve çok biçimlilik
class Sensor {
public:
    virtual ~Sensor() { std::cout << "  [~Sensor]\n"; }      // SANAL destructor
    virtual double oku() const = 0;                           // saf sanal: türemiş sınıf yazmak ZORUNDA
    virtual std::string ad() const { return "sensor"; }       // varsayılan sürüm, istenirse override edilir

    void bilgi() const {                                      // sanal değil ama sanal fonksiyonları çağırıyor
        std::cout << "  " << ad() << " = " << oku() << "\n";
    }
};

class Sicaklik : public Sensor {
public:
    ~Sicaklik() override { std::cout << "  [~Sicaklik]\n"; }
    double oku() const override { return 23.5; }
    std::string ad() const override { return "sicaklik"; }
};

class Gps : public Sensor {
public:
    ~Gps() override { std::cout << "  [~Gps]\n"; }
    double oku() const override { return 39.93; }
    // ad() override EDİLMEDİ: taban sınıftaki "sensor" kullanılır
};

// ---------------------------------------------------------------- 3) Constructor içinde sanal fonksiyon tuzağı
struct Taban {
    Taban() { ad(); }                                         // türemiş kısım henüz YOK
    virtual void ad() const { std::cout << "  Taban::ad\n"; }
    virtual ~Taban() = default;
};

struct Turemis : Taban {
    void ad() const override { std::cout << "  Turemis::ad\n"; }
};

// ---------------------------------------------------------------- 4) Bellekte sanal tablo işaretçisi
struct Bos {};
struct BosSanal {
    virtual void f() {}
};

int main() {
    std::cout << "--- 1) Sanal olmayan ve sanal fonksiyon ---\n";
    A* p = new B;     // taban pointer'ı, türemiş nesne
    std::cout << "  p->kimim()  : " << p->kimim() << "   <- pointer'in TIPINE bakar (A)\n";
    std::cout << "  p->kimimV() : " << p->kimimV() << "   <- nesnenin GERCEK tipine bakar (B)\n";
    delete p;         // A'nın destructor'ı sanal: sorun yok

    B b;
    A kopya = b;      // DILIMLEME (slicing): B'ye ait kısım kesilip atılır
    std::cout << "  dilimlenmis kopya.kimimV() : " << kopya.kimimV() << "   <- artik gercek bir A\n";
    A& ref = b;
    std::cout << "  ref.kimimV() (referans)    : " << ref.kimimV() << "   <- referansta dilimleme yok\n";

    std::cout << "\n--- 2) Cok bicimlilik ve sanal destructor ---\n";
    {
        std::vector<std::unique_ptr<Sensor>> sensorler;
        sensorler.push_back(std::make_unique<Sicaklik>());
        sensorler.push_back(std::make_unique<Gps>());
        for (const auto& s : sensorler) {
            s->bilgi();                                       // her biri KENDİ oku()/ad() fonksiyonunu çağırır
        }
        std::cout << "  vector yok oluyor...\n";
    }

    std::cout << "\n--- 3) Constructor icinde sanal fonksiyon ---\n";
    Turemis t;                                                // Taban() çalışırken Turemis kısmı yok
    std::cout << "  nesne hazir, simdi t.ad():\n";
    t.ad();

    std::cout << "\n--- 4) Sanal tablo isaretcisi (vptr) ---\n";
    std::cout << "  sizeof(Bos) = " << sizeof(Bos) << ", sizeof(BosSanal) = " << sizeof(BosSanal) << "\n";

    std::cout << "\n--- main sonu ---\n";
    return 0;
}
