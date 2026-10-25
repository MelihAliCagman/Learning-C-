// Konu: Onluk sayıyı ikiliye (ve ikiliyi onluğa) çevirmek
// Ne gösteriyor: Sürekli 2'ye bölüp kalanları ters sırayla dizmeyi; ikiliden onluğa Horner yöntemini.
// Neden önemli: Gömülü/haberleşme işlerinin temeli; bit işlemleriyle (10_bit_islemleri) bağlantılı.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 14_ondalik_ikili 14_ondalik_ikili.cpp

#include <iostream>
#include <string>

std::string ikiliyeCevir(unsigned n) {
    if (n == 0) {
        return "0";
    }
    std::string sonuc;
    while (n > 0) {
        sonuc.insert(sonuc.begin(), static_cast<char>('0' + n % 2));   // kalanı BAŞA ekle (ters sıra)
        n /= 2;
    }
    return sonuc;
}

unsigned onluyaCevir(const std::string& ikili) {
    unsigned sonuc = 0;
    for (char c : ikili) {
        sonuc = sonuc * 2 + (c == '1' ? 1u : 0u);    // her basamakta sola kaydır, yeni biti ekle
    }
    return sonuc;
}

int main() {
    for (unsigned n : {0u, 1u, 2u, 10u, 255u, 1024u}) {
        std::string b = ikiliyeCevir(n);
        std::cout << n << " -> " << b << " -> geri " << onluyaCevir(b) << "\n";
    }
    return 0;
}
