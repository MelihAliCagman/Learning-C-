// Konu: Bir sayı asal mı?
// Ne gösteriyor: Bölenleri kareköke kadar denemeyi (O(sqrt(n))), çiftleri baştan elemeyi, kenar durumları.
// Neden önemli: Her seviyede sorulan klasik; "nasıl optimize edersin?" takip sorusu gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 05_asal_mi 05_asal_mi.cpp

#include <iostream>

// n = a * b ise a ya da b en fazla sqrt(n)'dir: sqrt(n)'e kadar bakmak yeter.
// i * i <= n yazmak büyük n'de taşabilir; i <= n / i güvenlidir.
bool asalMi(long long n) {
    if (n < 2) {
        return false;            // 0, 1 ve negatifler asal değil
    }
    if (n < 4) {
        return true;             // 2 ve 3
    }
    if (n % 2 == 0) {
        return false;            // çiftleri ele
    }
    for (long long i = 3; i <= n / i; i += 2) {   // yalnızca tek bölenler
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    for (long long n : {-5LL, 0LL, 1LL, 2LL, 3LL, 4LL, 17LL, 25LL, 97LL, 7919LL, 1000000007LL}) {
        std::cout << n << (asalMi(n) ? " asal" : " asal degil") << "\n";
    }
    return 0;
}
