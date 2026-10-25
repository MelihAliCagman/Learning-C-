// Konu: Palindrom sayı (121, 12321 gibi, ters okununca aynı olan sayı)
// Ne gösteriyor: Sayıyı ters çevirip kendisiyle karşılaştırmayı; negatif sayı ve sondaki sıfır kenar durumlarını.
// Neden önemli: Ters çevirme sorusunun doğal devamı; kenar durumları sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 11_palindrom_sayi 11_palindrom_sayi.cpp

#include <iostream>

bool palindromMu(int n) {
    if (n < 0) {
        return false;            // -121 palindrom sayılmaz (ters okunuşu 121-)
    }
    long long orijinal = n;
    long long ters = 0;
    while (n > 0) {
        ters = ters * 10 + n % 10;
        n /= 10;
    }
    return ters == orijinal;
}

int main() {
    for (int n : {121, 123, 10, 0, -121, 12321, 1221, 7}) {
        std::cout << n << (palindromMu(n) ? " palindrom" : " palindrom degil") << "\n";
    }
    std::cout << "NOT: 10 -> ters 1; sondaki sifir yuzunden palindrom degil.\n";
    return 0;
}
