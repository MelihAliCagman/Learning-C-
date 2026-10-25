// Konu: Fibonacci sayıları
// Ne gösteriyor: Saf özyineli (yavaş), döngülü ve hafızalı (memoization) çözümü ve çağrı sayısı farkını.
// Neden önemli: "Özyinelemeyi nasıl hızlandırırsın?" sorusunun klasik örneği (dinamik programlamaya giriş).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 04_fibonacci 04_fibonacci.cpp

#include <cstdint>
#include <iostream>
#include <vector>

long long cagriSayisi = 0;

// O(2^n): aynı alt problemler tekrar tekrar hesaplanır.
std::uint64_t fibOzyineli(int n) {
    ++cagriSayisi;
    if (n < 2) {
        return static_cast<std::uint64_t>(n);
    }
    return fibOzyineli(n - 1) + fibOzyineli(n - 2);
}

// O(n) zaman, O(1) bellek: iki değişkeni kaydırarak ilerler.
std::uint64_t fibDongu(int n) {
    if (n < 2) {
        return static_cast<std::uint64_t>(n);
    }
    std::uint64_t onceki = 0;
    std::uint64_t simdiki = 1;
    for (int i = 2; i <= n; ++i) {
        std::uint64_t sonraki = onceki + simdiki;
        onceki = simdiki;
        simdiki = sonraki;
    }
    return simdiki;
}

// O(n): özyineli ama hesaplanan sonuçları saklar.
std::uint64_t fibHafizali(int n, std::vector<std::uint64_t>& hafiza) {
    if (n < 2) {
        return static_cast<std::uint64_t>(n);
    }
    std::size_t i = static_cast<std::size_t>(n);
    if (hafiza[i] != 0) {
        return hafiza[i];
    }
    hafiza[i] = fibHafizali(n - 1, hafiza) + fibHafizali(n - 2, hafiza);
    return hafiza[i];
}

int main() {
    std::cout << "Ilk 11 sayi: ";
    for (int i = 0; i <= 10; ++i) {
        std::cout << fibDongu(i) << " ";
    }
    std::cout << "\n";

    cagriSayisi = 0;
    std::cout << "fibOzyineli(30) = " << fibOzyineli(30) << ", cagri sayisi = " << cagriSayisi << "\n";
    std::cout << "fibDongu(30)    = " << fibDongu(30) << "\n";

    std::vector<std::uint64_t> hafiza(51, 0);
    std::cout << "fibHafizali(50) = " << fibHafizali(50, hafiza) << "\n";
    std::cout << "fibDongu(93)    = " << fibDongu(93) << "  (94'te uint64_t tasar)\n";
    return 0;
}
