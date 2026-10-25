// Konu: Kelime sıklığı (her kelime kaç kez geçiyor?)
// Ne gösteriyor: Metni kelimelere ayırmayı (istringstream), unordered_map ile saymayı ve sonucu sıralayıp yazdırmayı.
// Neden önemli: Canlı kodlama mülakatlarının klasik sorularından; unordered_map pratiği ve sıralama kuralı (beraberlik) sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 33_kelime_sikligi 33_kelime_sikligi.cpp

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::string kucukHarf(std::string s) {
    for (char& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return s;
}

// O(n) ortalama sayım + O(k log k) sıralama (k: farklı kelime sayısı).
std::vector<std::pair<std::string, int>> kelimeSikligi(const std::string& metin) {
    std::unordered_map<std::string, int> say;
    std::istringstream akim(metin);
    std::string kelime;
    while (akim >> kelime) {                       // boşluklara göre kelime kelime okur
        ++say[kucukHarf(kelime)];
    }
    std::vector<std::pair<std::string, int>> sonuc(say.begin(), say.end());
    // unordered_map sırası belirsiz: önce sayıya (çoktan aza), eşitse alfabetik sırala.
    std::sort(sonuc.begin(), sonuc.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    });
    return sonuc;
}

int main() {
    for (std::string metin : {"the cat and the dog and the bird", "Ali ali ALI veli", ""}) {
        std::cout << "\"" << metin << "\":\n";
        for (const auto& cift : kelimeSikligi(metin)) {
            std::cout << "  " << cift.first << " = " << cift.second << "\n";
        }
    }
    return 0;
}
