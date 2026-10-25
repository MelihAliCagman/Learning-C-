// Konu: Mükemmel sayı (kendisi hariç bölenlerinin toplamı kendisine eşit: 6 = 1 + 2 + 3)
// Ne gösteriyor: Bölenleri bulup toplamayı; kendisi hariç tutma ayrıntısını.
// Neden önemli: Döngü ve bölme (%) pratiği için temel soru.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 13_mukemmel_sayi 13_mukemmel_sayi.cpp

#include <iostream>

bool mukemmelMi(int n) {
    if (n < 2) {
        return false;
    }
    int toplam = 1;                       // 1 her sayının bölenidir (n kendisi hariç)
    for (int i = 2; i <= n / 2; ++i) {    // n'in yarısından büyük bölen olmaz (kendisi hariç)
        if (n % i == 0) {
            toplam += i;
        }
    }
    return toplam == n;
}

int main() {
    for (int n : {6, 28, 12, 1, 496}) {
        std::cout << n << (mukemmelMi(n) ? " mukemmel" : " mukemmel degil") << "\n";
    }
    std::cout << "10000'e kadar mukemmel sayilar: ";
    for (int n = 1; n <= 10000; ++n) {
        if (mukemmelMi(n)) {
            std::cout << n << " ";
        }
    }
    std::cout << "\n";
    return 0;
}
