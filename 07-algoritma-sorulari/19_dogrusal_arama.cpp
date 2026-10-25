// Konu: Doğrusal arama (linear search)
// Ne gösteriyor: Diziyi baştan sona gezip değeri bulmayı; bulunamayınca -1 dönmeyi.
// Neden önemli: En basit arama; ikili aramayla karşılaştırmak için taban çizgisi (O(n) ve O(log n)).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 19_dogrusal_arama 19_dogrusal_arama.cpp

#include <cstddef>
#include <iostream>
#include <vector>

// İlk bulunan indeksi döner, yoksa -1. Dizinin sıralı olması GEREKMEZ. O(n).
int dogrusalArama(const std::vector<int>& v, int aranan) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (v[i] == aranan) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {
    std::vector<int> v = {4, 8, 15, 16, 23, 42, 8};
    for (int aranan : {15, 8, 42, 99}) {
        int sonuc = dogrusalArama(v, aranan);
        if (sonuc >= 0) {
            std::cout << aranan << " bulundu, indeks = " << sonuc << "\n";
        } else {
            std::cout << aranan << " bulunamadi\n";
        }
    }
    std::cout << "bos dizide arama: " << dogrusalArama({}, 5) << "\n";
    std::cout << "NOT: 8 iki kez var, ilk indeks (1) donuyor.\n";
    return 0;
}
