// Konu: Dizide en sık geçen eleman
// Ne gösteriyor: unordered_map ile sayaç tutmayı; eşitlik (beraberlik) ve boş dizi kenar durumlarını.
// Neden önemli: Canlı kodlama mülakatlarının klasik sorularından biri; "frekans tablosu" kalıbının temeli.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 25_en_sik_eleman 25_en_sik_eleman.cpp

#include <iostream>
#include <unordered_map>
#include <vector>

// O(n) ortalama zaman, O(k) bellek (k: farklı eleman sayısı).
// Beraberlikte KÜÇÜK değeri seçiyoruz (unordered_map sırası belirsiz olduğu için kural koymak gerekir).
bool enSik(const std::vector<int>& v, int& deger, int& adet) {
    if (v.empty()) {
        return false;
    }
    std::unordered_map<int, int> say;
    for (int x : v) {
        ++say[x];                      // yoksa 0 ile oluşturur, sonra artırır
    }
    deger = v[0];
    adet = 0;
    for (const auto& cift : say) {
        if (cift.second > adet || (cift.second == adet && cift.first < deger)) {
            deger = cift.first;
            adet = cift.second;
        }
    }
    return true;
}

int main() {
    std::vector<std::vector<int>> testler = {{1, 3, 2, 3, 1, 3}, {4, 4, 5, 5}, {9}, {}};
    for (const auto& v : testler) {
        int deger = 0;
        int adet = 0;
        if (enSik(v, deger, adet)) {
            std::cout << "en sik eleman = " << deger << " (" << adet << " kez)\n";
        } else {
            std::cout << "bos dizi\n";
        }
    }
    std::cout << "NOT: {4,4,5,5} beraberlikte kucuk deger (4) secildi.\n";
    return 0;
}
