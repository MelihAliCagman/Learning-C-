// Konu: n'e kadar olan tüm asal sayıları bulmak (Eratosthenes eleği)
// Ne gösteriyor: Her sayıyı ayrı ayrı denemek yerine katları eleyerek çok daha hızlı çözümü.
// Neden önemli: "Çok sayıda asal gerekirse?" takip sorusunun cevabı; O(n log log n).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 06_asal_listesi 06_asal_listesi.cpp

#include <cstddef>
#include <iostream>
#include <vector>

// Fikir: 2'den başla; asal bulunca onun katlarını (i*i, i*i + i, ...) "asal değil" diye işaretle.
std::vector<int> asallar(int n) {
    std::vector<int> sonuc;
    if (n < 2) {
        return sonuc;
    }
    std::size_t son = static_cast<std::size_t>(n);
    std::vector<bool> asal(son + 1, true);
    for (std::size_t i = 2; i <= son; ++i) {
        if (!asal[i]) {
            continue;                                   // zaten bir sayının katı: asal değil
        }
        sonuc.push_back(static_cast<int>(i));
        for (std::size_t k = i * i; k <= son; k += i) {  // i*i'den başlamak yeter (küçük katlar daha önce elendi)
            asal[k] = false;
        }
    }
    return sonuc;
}

int main() {
    std::cout << "50'ye kadar asallar: ";
    for (int p : asallar(50)) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    std::cout << "100'e kadar asal sayisi    : " << asallar(100).size() << "\n";
    std::cout << "100000'e kadar asal sayisi : " << asallar(100000).size() << "\n";
    std::cout << "n = 1 icin liste bos mu?   : " << asallar(1).empty() << "\n";
    return 0;
}
