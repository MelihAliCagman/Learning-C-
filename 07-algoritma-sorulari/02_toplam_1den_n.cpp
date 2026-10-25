// Konu: 1'den n'e kadar sayıların toplamı
// Ne gösteriyor: Döngüyle O(n) ve formülle O(1) çözümü, int taşması.
// Neden önemli: "Daha hızlı yolu var mı?" sorusunun en basit örneği; taşma kontrolü alışkanlığı.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 02_toplam_1den_n 02_toplam_1den_n.cpp

#include <iostream>

// O(n): her sayıyı tek tek toplar.
long long toplamDongu(int n) {
    long long toplam = 0;
    for (int i = 1; i <= n; ++i) {
        toplam += i;
    }
    return toplam;
}

// O(1): Gauss formülü n * (n + 1) / 2.
long long toplamFormul(long long n) {
    return n * (n + 1) / 2;
}

int main() {
    for (int n : {0, 1, 10, 100, 100000}) {
        std::cout << "n = " << n << ": dongu = " << toplamDongu(n) << ", formul = " << toplamFormul(n) << "\n";
    }
    std::cout << "NOT: n = 100000 icin sonuc 5000050000, int'in siniri (2147483647) asildi: long long sart.\n";
    return 0;
}
