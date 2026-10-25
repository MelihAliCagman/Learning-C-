// Konu: Diziyi k adım sola döndürmek (rotate)
// Ne gösteriyor: Üç ters çevirme (reverse) ile yerinde döndürmeyi; k > n ve boş dizi kenar durumlarını.
// Neden önemli: Ters çevirme tekniğinin zekice bir uygulaması; "ek dizi kullanmadan" kısıtıyla sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 26_dizi_dondurme 26_dizi_dondurme.cpp

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

// Sola k adım: [1 2 3 4 5], k = 2 -> [3 4 5 1 2]
// Hile: önce ilk k elemanı, sonra kalanı, sonra hepsini ters çevir.  O(n) zaman, O(1) bellek.
void solaDondur(std::vector<int>& v, std::size_t k) {
    if (v.empty()) {
        return;
    }
    k %= v.size();                                   // k, n'den büyükse tam turları atla
    std::reverse(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(k));
    std::reverse(v.begin() + static_cast<std::ptrdiff_t>(k), v.end());
    std::reverse(v.begin(), v.end());
}

int main() {
    struct Test { std::vector<int> v; std::size_t k; };
    for (Test t : {Test{{1, 2, 3, 4, 5}, 2}, Test{{1, 2, 3, 4, 5}, 7}, Test{{1, 2, 3}, 0}, Test{{9}, 3}, Test{{}, 2}}) {
        yaz("once : ", t.v);
        solaDondur(t.v, t.k);
        std::cout << "k = " << t.k << " ";
        yaz("sonra: ", t.v);
    }
    return 0;
}
