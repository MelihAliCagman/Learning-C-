// Konu: Başlık/kaynak ayrımı, include guard, namespace, extern, makro tuzakları ve derleme süreci
// Ne gösteriyor: Bildirim (.h) ile tanımı (.cpp) ayırmayı, çok dosyalı bir programın nasıl derlenip bağlandığını ve #define tuzağını.
// Neden önemli: Gerçek projeler çok dosyalıdır; "multiple definition", "undefined reference" ve "include guard" mülakatın klasik soruları.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 15_proje main.cpp telemetri.cpp cihazlar.cpp

#include <iostream>

#include "cihazlar.h"    // içinde telemetri.h de var
#include "telemetri.h"   // ikinci kez: include guard sayesinde zararsız

// ---------------------------------------------------------------- Makro tuzağı
// Makro, derleyiciye değil ÖNİŞLEMCİYE aittir: metin değiştirir, tip ve öncelik bilmez.
#define KARE_KOTU(x) x * x
#define KARE_IYI(x) ((x) * (x))

int main() {
    std::cout << "--- 1) Makro tuzagi ---\n";
    std::cout << "KARE_KOTU(1 + 2) = " << KARE_KOTU(1 + 2) << "   (1 + 2 * 1 + 2 olarak acilir!)\n";
    std::cout << "KARE_IYI(1 + 2)  = " << KARE_IYI(1 + 2) << "\n";
    std::cout << "telemetri::kare(1 + 2) = " << telemetri::kare(1 + 2) << "   (inline fonksiyon: dogru ve tip guvenli)\n";
    std::cout << "__FILE__ = " << __FILE__ << ", __LINE__ = " << __LINE__ << "\n";

    std::cout << "\n--- 2) namespace ---\n";
    sensor::yaz();
    motor::yaz();   // ikisi de 'yaz': namespace sayesinde cakismadi

    using telemetri::Olcum;   // sadece bu ismi getir (using namespace telemetri; DEGIL)
    Olcum o[3] = {{1, 20.5}, {2, 21.0}, {3, 19.55}};

    std::cout << "\n--- 3) extern ve ayri .cpp'de tanimlanan fonksiyon ---\n";
    std::cout << "toplamOlcum (once)  = " << telemetri::toplamOlcum << "\n";
    std::cout << "ortalama            = " << telemetri::ortalama(o, 3) << "\n";
    std::cout << "toplamOlcum (sonra) = " << telemetri::toplamOlcum << "\n";
    std::cout << telemetri::metin(o[2]) << "\n";
    std::cout << "MAKS_OLCUM = " << telemetri::MAKS_OLCUM << "\n";

    return 0;
}
