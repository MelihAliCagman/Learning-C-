// Konu: Dizideki ikinci en büyük eleman
// Ne gösteriyor: Tek geçişte iki değer takip etmeyi; tekrar eden elemanlar ve eleman sayısı yetersiz kenar durumlarını.
// Neden önemli: "Sıralamadan çöz" sorusu; kenar durumları dikkatli düşünmeyi ölçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 18_ikinci_en_buyuk 18_ikinci_en_buyuk.cpp

#include <iostream>
#include <vector>

// "İkinci en büyük", en büyükten KÜÇÜK olan en büyük değerdir ({5, 5, 3} için 3).
// O(n) zaman, O(1) bellek. Birinci/ikinci değerin var olup olmadığını ayrı bayraklarla tutuyoruz.
bool ikinciEnBuyuk(const std::vector<int>& v, int& sonuc) {
    bool birVar = false;
    bool ikiVar = false;
    int en = 0;
    int ikinci = 0;
    for (int x : v) {
        if (!birVar || x > en) {
            if (birVar) {
                ikinci = en;          // eski en büyük ikinci oldu
                ikiVar = true;
            }
            en = x;
            birVar = true;
        } else if (x < en && (!ikiVar || x > ikinci)) {
            ikinci = x;
            ikiVar = true;
        }
    }
    if (!ikiVar) {
        return false;                 // en az iki FARKLI değer yok
    }
    sonuc = ikinci;
    return true;
}

int main() {
    std::vector<std::vector<int>> testler = {{5, 3, 9, 7}, {5, 5, 3}, {4, 4, 4}, {10}, {}, {-1, -5, -3}, {1, 2}};
    for (const auto& v : testler) {
        int s = 0;
        std::cout << "eleman sayisi " << v.size() << ": ";
        if (ikinciEnBuyuk(v, s)) {
            std::cout << "ikinci en buyuk = " << s << "\n";
        } else {
            std::cout << "yok (en az iki farkli deger gerekir)\n";
        }
    }
    return 0;
}
