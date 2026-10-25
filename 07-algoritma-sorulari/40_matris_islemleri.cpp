// Konu: İki boyutlu dizi (matris): toplam, köşegen toplamı ve devrik (transpose)
// Ne gösteriyor: vector<vector<int>> ile satır/sütun gezmeyi, [i][i] köşegenini ve [i][j] <-> [j][i] devriği.
// Neden önemli: İç içe döngü ve indeks mantığı; matris soruları yeni başlayan mülakatlarında çok geçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 40_matris_islemleri 40_matris_islemleri.cpp

#include <cstddef>
#include <iostream>
#include <vector>

using Matris = std::vector<std::vector<int>>;

void yaz(const char* etiket, const Matris& m) {
    std::cout << etiket << "\n";
    for (const auto& satir : m) {
        std::cout << "  ";
        for (int x : satir) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}

int elemanToplami(const Matris& m) {
    int toplam = 0;
    for (const auto& satir : m) {
        for (int x : satir) {
            toplam += x;
        }
    }
    return toplam;
}

// Kare matris varsayımı: ana köşegen = [0][0], [1][1], ...
int kosegenToplami(const Matris& m) {
    int toplam = 0;
    for (std::size_t i = 0; i < m.size(); ++i) {
        toplam += m[i][i];
    }
    return toplam;
}

// Devrik: satırlar sütun olur. n x m matris -> m x n matris.
Matris devrik(const Matris& m) {
    if (m.empty()) {
        return {};
    }
    Matris sonuc(m[0].size(), std::vector<int>(m.size()));
    for (std::size_t i = 0; i < m.size(); ++i) {
        for (std::size_t j = 0; j < m[i].size(); ++j) {
            sonuc[j][i] = m[i][j];
        }
    }
    return sonuc;
}

int main() {
    Matris m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    yaz("Matris:", m);
    std::cout << "eleman toplami  = " << elemanToplami(m) << "\n";
    std::cout << "kosegen toplami = " << kosegenToplami(m) << "  (1 + 5 + 9)\n";
    yaz("Devrik:", devrik(m));

    Matris dikdortgen = {{1, 2, 3}, {4, 5, 6}};
    yaz("2x3 matris:", dikdortgen);
    yaz("Devrigi (3x2):", devrik(dikdortgen));
    return 0;
}
