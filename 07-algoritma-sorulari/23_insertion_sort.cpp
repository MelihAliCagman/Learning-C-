// Konu: Araya ekleme sıralaması (insertion sort)
// Ne gösteriyor: Elemanı, solundaki sıralı kısımda doğru yere kaydırarak yerleştirmeyi (iskambil elinde kart dizmek gibi).
// Neden önemli: Küçük ve neredeyse sıralı veride en hızlı basit sıralama (en iyi durum O(n)); STL sıralaması küçük parçalarda bunu kullanır.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 23_insertion_sort 23_insertion_sort.cpp

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

// En kötü O(n^2), en iyi (zaten sıralı) O(n). Yerinde, kararlı. Dönüş: kaydırma sayısı.
int insertionSort(std::vector<int>& v) {
    int kaydirma = 0;
    for (std::size_t i = 1; i < v.size(); ++i) {
        int anahtar = v[i];              // yerleştirilecek eleman
        std::size_t j = i;
        while (j > 0 && v[j - 1] > anahtar) {
            v[j] = v[j - 1];             // büyükleri sağa kaydır
            --j;
            ++kaydirma;
        }
        v[j] = anahtar;                  // boşalan yere koy
    }
    return kaydirma;
}

int main() {
    std::vector<std::vector<int>> testler = {{5, 2, 9, 1, 5, 6}, {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}, {7}, {}};
    for (auto v : testler) {
        yaz("once : ", v);
        int k = insertionSort(v);
        yaz("sonra: ", v);
        std::cout << "kaydirma sayisi = " << k << "\n\n";
    }
    std::cout << "NOT: zaten sirali dizide kaydirma 0: en iyi durum O(n).\n";
    return 0;
}
