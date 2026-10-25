// Konu: Bir sayının basamakları: basamak toplamı ve basamak sayısı
// Ne gösteriyor: % 10 ile son basamağı almayı, / 10 ile son basamağı atmayı.
// Neden önemli: Sayıyı basamaklarına ayırma kalıbı (ters çevirme, palindrom, Armstrong sorularının temeli).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 09_basamak_islemleri 09_basamak_islemleri.cpp

#include <iostream>

int basamakToplami(long long n) {
    if (n < 0) {
        n = -n;
    }
    int toplam = 0;
    while (n > 0) {
        toplam += static_cast<int>(n % 10);   // son basamağı al
        n /= 10;                              // son basamağı at
    }
    return toplam;
}

int basamakSayisi(long long n) {
    if (n == 0) {
        return 1;                             // 0 tek basamaklıdır
    }
    if (n < 0) {
        n = -n;
    }
    int sayac = 0;
    while (n > 0) {
        ++sayac;
        n /= 10;
    }
    return sayac;
}

int main() {
    for (long long n : {12345LL, 0LL, 7LL, -907LL, 1000000LL}) {
        std::cout << n << ": basamak toplami = " << basamakToplami(n) << ", basamak sayisi = " << basamakSayisi(n) << "\n";
    }
    return 0;
}
