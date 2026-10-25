// Konu: Faktöriyel
// Ne gösteriyor: Döngülü ve özyineli çözümü, 0! = 1 kuralını, 20!'den sonra taşmayı.
// Neden önemli: Özyinelemenin (recursion) en klasik örneği; taban durum ve taşma sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 03_faktoriyel 03_faktoriyel.cpp

#include <cstdint>
#include <iostream>

// Döngülü: O(n) zaman, O(1) bellek. 20! uint64_t'ye sığar, 21! sığmaz.
bool faktoriyel(int n, std::uint64_t& sonuc) {
    if (n < 0 || n > 20) {
        return false;
    }
    sonuc = 1;
    for (int i = 2; i <= n; ++i) {
        sonuc *= static_cast<std::uint64_t>(i);
    }
    return true;
}

// Özyineli: O(n) zaman, O(n) stack.
std::uint64_t faktoriyelOzyineli(int n) {
    if (n <= 1) {            // taban durum: bu olmazsa sonsuz özyineleme
        return 1;
    }
    return static_cast<std::uint64_t>(n) * faktoriyelOzyineli(n - 1);
}

int main() {
    for (int n : {0, 1, 5, 10, 20, 21, -3}) {
        std::uint64_t f = 0;
        if (faktoriyel(n, f)) {
            std::cout << n << "! = " << f << "\n";
        } else {
            std::cout << n << "! hesaplanamadi (negatif ya da tasar)\n";
        }
    }
    std::cout << "ozyineli 6! = " << faktoriyelOzyineli(6) << "\n";
    return 0;
}
