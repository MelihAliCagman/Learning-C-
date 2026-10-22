// Konu: Signed/unsigned tuzakları, taşma (overflow) ve tip dönüşümleri
// Ne gösteriyor: İşaretli ve işaretsiz tamsayıların karşılaştırma ve taşma davranışındaki farkı.
// Neden önemli: Döngü indeksi, boyut hesabı ve sensör verisinde sessizce yanlış sonuç üreten klasik hata kaynağı; mülakatta sık sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 05_signed_unsigned 05_signed_unsigned.cpp

#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    // 1) İşaretsiz taşma: başa sarar (tanımlı davranış).
    uint8_t a = 250;
    a = a + 10;
    std::cout << "1) uint8_t 250 + 10 = " << static_cast<int>(a) << "\n";

    // 2) İşaretsiz tipte "eksi": 0'dan 1 çıkarırsan ne olur?
    unsigned int u = 0;
    u = u - 1;
    std::cout << "2) unsigned int 0 - 1 = " << u << "\n";

    // 3) İşaretli ile işaretsizi karşılaştırmak (klasik tuzak).
    int eksi = -1;
    unsigned int bir = 1;
    // Derleme sırasında -Wall -Wextra bir uyarı verecek; uyarıyı oku ve buraya yorumla.
    std::cout << "3a) int -1 < unsigned int 1 = " << (eksi < bir ? "true" : "false") << "\n";
    std::cout << "3b) int -1 < unsigned int 1 = " << (eksi < static_cast<int>(bir) ? "true" : "false") << "\n";    
    
    // 4) Vektör boyutu da işaretsizdir (size_t).
    std::vector<int> bos;
    std::cout << "4) bos.size() - 1 = " << bos.size() - 1 << "\n";
    return 0;
}
