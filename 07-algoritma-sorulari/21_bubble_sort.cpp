// Konu: Kabarcık sıralaması (bubble sort)
// Ne gösteriyor: Komşu elemanları karşılaştırıp yer değiştirerek büyükleri sona "kabarcık gibi" taşımayı; erken çıkış optimizasyonunu.
// Neden önemli: En basit sıralama; O(n^2) olduğunu ve neden verimsiz olduğunu anlatabilmek istenir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 21_bubble_sort 21_bubble_sort.cpp

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

void yaz(const char* etiket, const std::vector<int>& v) {
    std::cout << etiket;
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

// Her turda en büyük kalan eleman sona yerleşir. Hiç takas olmadıysa dizi zaten sıralıdır: erken çık.
// En kötü durum O(n^2), en iyi durum (zaten sıralı) O(n). Yerinde (O(1) ek bellek), kararlı (stable).
int bubbleSort(std::vector<int>& v) {
    int takasSayisi = 0;
    for (std::size_t tur = 0; tur + 1 < v.size(); ++tur) {
        bool degisti = false;
        for (std::size_t j = 0; j + 1 < v.size() - tur; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                ++takasSayisi;
                degisti = true;
            }
        }
        if (!degisti) {
            break;
        }
    }
    return takasSayisi;
}

int main() {
    std::vector<std::vector<int>> testler = {{5, 2, 9, 1, 5, 6}, {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}, {7}, {}};
    for (auto v : testler) {
        yaz("once : ", v);
        int takas = bubbleSort(v);
        yaz("sonra: ", v);
        std::cout << "takas sayisi = " << takas << "\n\n";
    }
    return 0;
}
