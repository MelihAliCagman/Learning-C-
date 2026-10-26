// Konu: Maksimum alt dizi toplamı (maximum subarray, Kadane algoritması)
// Ne gösteriyor: Ardışık elemanlardan oluşan en büyük toplamlı parçayı tek geçişte (O(n)) bulmayı; hepsi negatif kenar durumunu.
// Neden önemli: Dinamik programlamaya giriş sorusu; "O(n^2) çözümü O(n)'e nasıl indirirsin?" takibi gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 43_kadane_maksimum_alt_dizi 43_kadane_maksimum_alt_dizi.cpp

#include <cstddef>
#include <iostream>
#include <vector>

// Kadane: her konumda şunu sor: "önceki parçaya devam etmek mi, yeni parça başlatmak mı daha iyi?"
//   suAnki = max(v[i], suAnki + v[i])     (önceki toplam negatifse yeni parça başlat)
//   enIyi  = max(enIyi, suAnki)
// O(n) zaman, O(1) bellek. Boş dizide sonuç yok: false döner.
bool kadane(const std::vector<int>& v, long long& enIyi, std::size_t& bas, std::size_t& son) {
    if (v.empty()) {
        return false;
    }
    long long suAnki = v[0];
    enIyi = v[0];
    std::size_t gecici = 0;                     // şu anki parçanın başı
    bas = 0;
    son = 0;
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (suAnki < 0) {                       // önceki parça zarar veriyor: yeni parça başlat
            suAnki = v[i];
            gecici = i;
        } else {
            suAnki += v[i];
        }
        if (suAnki > enIyi) {
            enIyi = suAnki;
            bas = gecici;
            son = i;
        }
    }
    return true;
}

// Kontrol için kaba kuvvet: tüm alt dizileri dene. O(n^2).
long long kabaKuvvet(const std::vector<int>& v) {
    long long enIyi = v[0];
    for (std::size_t i = 0; i < v.size(); ++i) {
        long long toplam = 0;
        for (std::size_t j = i; j < v.size(); ++j) {
            toplam += v[j];
            if (toplam > enIyi) {
                enIyi = toplam;
            }
        }
    }
    return enIyi;
}

int main() {
    std::vector<std::vector<int>> testler = {
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},   // en iyi: [4, -1, 2, 1] = 6
        {1, 2, 3, 4},                      // hepsi pozitif: tamamı = 10
        {-3, -1, -2},                      // hepsi negatif: en az negatif eleman = -1
        {5},
        {8, -19, 5, -4, 20},               // en iyi: [5, -4, 20] = 21 (8'i bırakıp yeni parça başlatmak)
        {}};
    for (const auto& v : testler) {
        long long sonuc = 0;
        std::size_t bas = 0;
        std::size_t son = 0;
        if (!kadane(v, sonuc, bas, son)) {
            std::cout << "bos dizi: sonuc yok\n";
            continue;
        }
        std::cout << "en iyi toplam = " << sonuc << "  parca: [";
        for (std::size_t i = bas; i <= son; ++i) {
            std::cout << v[i] << (i < son ? ", " : "");
        }
        std::cout << "]  (kaba kuvvet: " << kabaKuvvet(v) << (kabaKuvvet(v) == sonuc ? " ayni)" : " FARKLI!)") << "\n";
    }
    return 0;
}
