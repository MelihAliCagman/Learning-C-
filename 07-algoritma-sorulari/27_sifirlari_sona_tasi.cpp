// Konu: Sıfırları dizinin sonuna taşımak (diğer elemanların sırası bozulmadan)
// Ne gösteriyor: Okuma ve yazma indeksiyle tek geçişte yerinde çözümü.
// Neden önemli: "İki işaretçi (two pointers)" kalıbının güzel bir örneği: O(n) zaman, O(1) bellek.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 27_sifirlari_sona_tasi 27_sifirlari_sona_tasi.cpp

#include <cstddef>
#include <iostream>
#include <vector>

void yaz(const char* etiket, const std::vector<int>& v) {
    std::cout << etiket;
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

// [0 1 0 3 12] -> [1 3 12 0 0]
void sifirlariSonaTasi(std::vector<int>& v) {
    std::size_t yaz = 0;                      // sıfır olmayanların yazılacağı yer
    for (std::size_t oku = 0; oku < v.size(); ++oku) {
        if (v[oku] != 0) {
            v[yaz] = v[oku];
            ++yaz;
        }
    }
    while (yaz < v.size()) {                  // kalan yerleri sıfırla doldur
        v[yaz] = 0;
        ++yaz;
    }
}

int main() {
    std::vector<std::vector<int>> testler = {{0, 1, 0, 3, 12}, {1, 2, 3}, {0, 0, 0}, {0}, {}};
    for (auto v : testler) {
        yaz("once : ", v);
        sifirlariSonaTasi(v);
        yaz("sonra: ", v);
    }
    return 0;
}
