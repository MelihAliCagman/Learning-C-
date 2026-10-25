// Konu: Seçmeli sıralama (selection sort)
// Ne gösteriyor: Her turda kalan kısmın en küçüğünü bulup başa yerleştirmeyi; takas sayısının az olmasını.
// Neden önemli: Bubble ve insertion ile karşılaştırılır: hep O(n^2) karşılaştırma ama en çok n-1 takas yapar.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 22_selection_sort 22_selection_sort.cpp

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

// O(n^2) zaman (sıralı dizide bile), O(1) ek bellek, en çok n-1 takas. Kararlı DEĞİL.
int selectionSort(std::vector<int>& v) {
    int takasSayisi = 0;
    for (std::size_t i = 0; i + 1 < v.size(); ++i) {
        std::size_t enKucukIndeks = i;
        for (std::size_t j = i + 1; j < v.size(); ++j) {
            if (v[j] < v[enKucukIndeks]) {
                enKucukIndeks = j;
            }
        }
        if (enKucukIndeks != i) {
            std::swap(v[i], v[enKucukIndeks]);
            ++takasSayisi;
        }
    }
    return takasSayisi;
}

int main() {
    std::vector<std::vector<int>> testler = {{5, 2, 9, 1, 5, 6}, {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}, {7}, {}};
    for (auto v : testler) {
        yaz("once : ", v);
        int takas = selectionSort(v);
        yaz("sonra: ", v);
        std::cout << "takas sayisi = " << takas << "\n\n";
    }
    return 0;
}
