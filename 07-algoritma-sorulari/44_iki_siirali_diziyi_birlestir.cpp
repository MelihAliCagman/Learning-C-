// Konu: İki sıralı diziyi tek sıralı dizide birleştirmek (merge)
// Ne gösteriyor: İki işaretçiyle (her dizi için bir indeks) tek geçişte O(n + m) birleştirmeyi; boş dizi ve kalan elemanlar kenar durumlarını.
// Neden önemli: Merge sort algoritmasının kalbi; iki işaretçi tekniğinin güzel bir örneği ("sıralayıp birleştirmek" neden O((n+m) log) değil O(n+m)?).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 44_iki_siirali_diziyi_birlestir 44_iki_siirali_diziyi_birlestir.cpp

#include <algorithm>
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

// İki dizi de SIRALI olmalı. Her adımda iki dizinin başındaki küçük eleman sonuca alınır.
// O(n + m) zaman, O(n + m) bellek (sonuç dizisi).
std::vector<int> birlestir(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> sonuc;
    sonuc.reserve(a.size() + b.size());          // gereksiz yeniden tahsisi önler
    std::size_t i = 0;
    std::size_t j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {                      // <= : eşitlikte a'dan al (kararlı/stable birleştirme)
            sonuc.push_back(a[i]);
            ++i;
        } else {
            sonuc.push_back(b[j]);
            ++j;
        }
    }
    while (i < a.size()) {                       // a'da kalanlar zaten sıralı: olduğu gibi ekle
        sonuc.push_back(a[i]);
        ++i;
    }
    while (j < b.size()) {                       // b'de kalanlar
        sonuc.push_back(b[j]);
        ++j;
    }
    return sonuc;
}

int main() {
    struct Test { std::vector<int> a; std::vector<int> b; };
    for (Test t : {Test{{1, 3, 5, 7}, {2, 4, 6, 8}}, Test{{1, 2, 3}, {10, 20}}, Test{{5, 6}, {1, 2, 3}},
                   Test{{1, 3, 3}, {3, 3, 4}}, Test{{}, {4, 5}}, Test{{9}, {}}, Test{{}, {}}}) {
        yaz("a      : ", t.a);
        yaz("b      : ", t.b);
        std::vector<int> sonuc = birlestir(t.a, t.b);
        yaz("birlesim: ", sonuc);

        std::vector<int> kutuphane(t.a.size() + t.b.size());
        std::merge(t.a.begin(), t.a.end(), t.b.begin(), t.b.end(), kutuphane.begin());
        std::cout << "std::merge ile ayni mi? " << (kutuphane == sonuc) << "\n\n";
    }
    return 0;
}
