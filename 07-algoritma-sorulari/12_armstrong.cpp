// Konu: Armstrong sayısı (153 = 1^3 + 5^3 + 3^3)
// Ne gösteriyor: Basamakların, basamak sayısı kadar kuvvetlerinin toplamını hesaplamayı.
// Neden önemli: Basamak işlemleri ve döngü pratiği; yeni başlayan mülakatlarında sık gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 12_armstrong 12_armstrong.cpp

#include <iostream>

int basamakSayisi(int n) {
    int sayac = 0;
    while (n > 0) {
        ++sayac;
        n /= 10;
    }
    return sayac;
}

long long us(int taban, int kuvvet) {
    long long sonuc = 1;
    for (int i = 0; i < kuvvet; ++i) {
        sonuc *= taban;
    }
    return sonuc;
}

bool armstrongMu(int n) {
    if (n < 1) {
        return false;
    }
    int k = basamakSayisi(n);
    long long toplam = 0;
    for (int t = n; t > 0; t /= 10) {
        toplam += us(t % 10, k);       // her basamağın k. kuvveti
    }
    return toplam == n;
}

int main() {
    std::cout << "153 -> " << (armstrongMu(153) ? "armstrong" : "degil") << "\n";
    std::cout << "154 -> " << (armstrongMu(154) ? "armstrong" : "degil") << "\n";
    std::cout << "1000'e kadar armstrong sayilar: ";
    for (int n = 1; n <= 1000; ++n) {
        if (armstrongMu(n)) {
            std::cout << n << " ";
        }
    }
    std::cout << "\n";
    return 0;
}
