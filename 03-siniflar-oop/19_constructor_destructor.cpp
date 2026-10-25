// Konu: Constructor çeşitleri, initializer list ve destructor
// Ne gösteriyor: Nesnenin oluşum/yok oluş sırasını, kopya constructor'ın ne zaman çağrıldığını ve üye başlatma sırası tuzağını.
// Neden önemli: Constructor/destructor RAII'nin temelidir; "yok oluş sırası", "initializer list neden" ve "kopya constructor ne zaman" mülakatın klasikleridir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 19_constructor_destructor 19_constructor_destructor.cpp

#include <iostream>
#include <string>

class Sensor {
    std::string ad_;
    int id_;

public:
    // (1) Varsayılan constructor: parametresiz.
    Sensor() : ad_("bilinmiyor"), id_(0) {
        std::cout << "  [ctor  varsayilan] " << ad_ << "#" << id_ << "\n";
    }

    // (2) Parametreli constructor: üyeleri INITIALIZER LIST ile başlat (gövdede atama yapma).
    Sensor(const std::string& ad, int id) : ad_(ad), id_(id) {
        std::cout << "  [ctor  parametreli] " << ad_ << "#" << id_ << "\n";
    }

    // (3) Kopya constructor: başka bir Sensor'dan kopya oluşturur.
    Sensor(const Sensor& diger) : ad_(diger.ad_), id_(diger.id_) {
        std::cout << "  [ctor  KOPYA] " << ad_ << "#" << id_ << "\n";
    }

    // (4) Destructor: nesne yok olurken çağrılır.
    ~Sensor() {
        std::cout << "  [dtor] " << ad_ << "#" << id_ << "\n";
    }

    void yaz() const {
        std::cout << "  yaz: " << ad_ << "#" << id_ << "\n";
    }
};

// Değerle alır: parametre bir KOPYA olarak oluşturulur.
void goster(Sensor s) {
    std::cout << "  goster() icinde\n";
    s.yaz();
}

// Üye başlatma sırası tuzağı: üyeler DEĞİŞKENLERİN TANIMLANMA SIRASINA göre başlatılır,
// initializer list'teki yazım sırasına göre DEĞİL.
// UYARI VERİR (bilerek): -Wreorder
class Sirali {
public:
    int a_;
    int b_;
    explicit Sirali(int x) : b_(x), a_(b_ + 1) {}   // a_ ÖNCE başlatılır; o sırada b_ henüz belirsiz
};

int main() {
    std::cout << "--- 1) Kapsam ve sira ---\n";
    {
        Sensor a;
        Sensor b("gps", 2);
        Sensor c = b;      // dikkat: bu atama DEĞİL, başlatma
        Sensor d(b);
        std::cout << "  blok sonu\n";
    }

    std::cout << "\n--- 2) Heap ---\n";
    Sensor* p = new Sensor("imu", 3);
    delete p;

    std::cout << "\n--- 3) Fonksiyona deger olarak ---\n";
    Sensor lidar("lidar", 4);
    goster(lidar);
    std::cout << "  goster() bitti\n";

    std::cout << "\n--- 4) Uye baslatma sirasi ---\n";
    Sirali s(10);
    std::cout << "  b_ = " << s.b_ << " (beklenen 10)\n";
    std::cout << "  a_ = " << s.a_ << " (11 beklenirdi ama a_, b_'den ONCE baslatildigi icin cop deger)\n";

    std::cout << "\n--- main sonu ---\n";
    return 0;
}
