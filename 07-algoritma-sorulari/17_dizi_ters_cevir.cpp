// Konu: Diziyi ters çevirmek (yerinde, ek dizi kullanmadan)
// Ne gösteriyor: İki indeks (baştan ve sondan) yaklaşımını ve ortada buluşma koşulunu.
// Neden önemli: "İki işaretçi (two pointers)" tekniğinin en basit örneği; birçok sorunun temeli.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 17_dizi_ters_cevir 17_dizi_ters_cevir.cpp

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

// O(n) zaman, O(1) ek bellek.
void tersCevir(std::vector<int>& v) {
    if (v.size() < 2) {              // boş ya da tek eleman: yapılacak bir şey yok (v.size() - 1 boşta taşardı)
        return;
    }
    std::size_t sol = 0;
    std::size_t sag = v.size() - 1;
    while (sol < sag) {
        std::swap(v[sol], v[sag]);
        ++sol;
        --sag;
    }
}

int main() {
    std::vector<std::vector<int>> testler = {{1, 2, 3, 4, 5}, {1, 2, 3, 4}, {7}, {}};
    for (auto v : testler) {         // kopya alıyoruz ki orijinal test verisi bozulmasın
        yaz("once : ", v);
        tersCevir(v);
        yaz("sonra: ", v);
    }
    return 0;
}
