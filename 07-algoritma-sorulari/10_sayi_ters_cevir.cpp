// Konu: Bir sayıyı ters çevirmek (12345 -> 54321)
// Ne gösteriyor: Basamakları tek tek alıp ters sırayla yeniden kurmayı; taşma ve negatif sayı kenar durumlarını.
// Neden önemli: Çok sorulur; "taşarsa ne olur?" takip sorusu gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 10_sayi_ters_cevir 10_sayi_ters_cevir.cpp

#include <iostream>

// Ters sayı = ters * 10 + son basamak. long long kullanıyoruz: 1999999999 ters çevrilince int'e sığmaz.
long long tersSayi(long long n) {
    bool negatif = n < 0;
    if (negatif) {
        n = -n;
    }
    long long ters = 0;
    while (n > 0) {
        ters = ters * 10 + n % 10;
        n /= 10;
    }
    return negatif ? -ters : ters;
}

int main() {
    for (long long n : {12345LL, 1200LL, 7LL, 0LL, -123LL, 1999999999LL}) {
        std::cout << n << " -> " << tersSayi(n) << "\n";
    }
    std::cout << "NOT: 1200 -> 21 (bastaki sifirlar kaybolur), 1999999999 -> 9999999991 (int'e sigmaz).\n";
    return 0;
}
