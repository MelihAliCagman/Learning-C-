// Konu: Scope (kapsam), ömür (lifetime) ve static kullanımları
// Ne gösteriyor: Yerel değişkenin ömrünü, iç içe kapsamda aynı isimli değişkeni ve static'in iki kullanımını (yerel static, sınıf üyesi).
// Neden önemli: "static ne işe yarar?" mülakatın en sık sorularından biri; sayaç, tekil kaynak ve nesne sayımı gibi yerlerde kullanılır.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 06_scope_static 06_scope_static.cpp

#include <iostream>

// (A) Her çağrıda sıfırdan başlayan sayaç: yerel değişken fonksiyon bitince yok olur.
int sayacNormal() {
    int n = 0;
    n++;
    return n;
}

// (B) Değeri çağrılar arasında hatırlayan sayaç.
int sayacStatic() {
    static int n = 0;
    n++;
    return n;
}

// (C) Sınıf üyesi static: tüm nesneler arasında paylaşılan tek bir değişken.
struct Sensor {
    inline static int adet = 0;   // C++17: sınıf içinde tanımlanabilir

    Sensor() { adet++; }
    ~Sensor() { adet--; }
};

int main() {
    // 1) İç içe kapsam: aynı isimli iki değişken.
    int x = 10;
    {
        int x = 20;
        std::cout << "ic blok x = " << x << "\n";
    }
    std::cout << "dis blok x = " << x << "\n";

    // 2) Yerel değişken ve yerel static, üç çağrıda nasıl davranır?
    std::cout << "sayacNormal(1) = " << sayacNormal() << "\n";
    std::cout << "sayacNormal(2) = " << sayacNormal() << "\n";
    std::cout << "sayacNormal(3) = " << sayacNormal() << "\n";

    // TODO: sen yaz (sayacStatic()'i 3 kez çağırıp sonuçları yazdır)
    std::cout << "sayacStatic(1) = " << sayacStatic() << "\n";
    std::cout << "sayacStatic(2) = " << sayacStatic() << "\n";
    std::cout << "sayacStatic(3) = " << sayacStatic() << "\n";

    // 3) Sınıf üyesi static: nesne sayısı.
    std::cout << "baslangic adet = " << Sensor::adet << "\n";
    Sensor s1;
    Sensor s2;
    std::cout << "s1 ve s2 olusturulduktan sonra adet = " << Sensor::adet << "\n";
    {
        Sensor s3;
        std::cout << "s3 olusturulduktan sonra adet = " << Sensor::adet << "\n";
    }
    // TODO: sen yaz (s3 kapsamdan çıktı; Sensor::adet değerini yazdır)
    std::cout << "s3 kapsamdan cikti; adet = " << Sensor::adet << "\n";

    return 0;
}
