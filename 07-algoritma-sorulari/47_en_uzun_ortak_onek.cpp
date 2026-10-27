// Konu: Kelimelerin en uzun ortak öneki (longest common prefix)
// Ne gösteriyor: Önek adayını her kelimeyle karşılaştırıp kısaltan yöntemi ve "sırala, ilk ile sonu karşılaştır" hilesini; boş girdi ve boş önek kenar durumlarını.
// Neden önemli: Çok sorulan string sorusu; aynı soruya iki farklı yaklaşım anlatabilmek puan getirir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 47_en_uzun_ortak_onek 47_en_uzun_ortak_onek.cpp

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// Yöntem 1: İlk kelimeyi aday önek al; her kelimeyle karşılaştırıp aday öneki kısalt.
// O(S) zaman (S: tüm karakterlerin toplamı), O(1) ek bellek.
std::string ortakOnek(const std::vector<std::string>& kelimeler) {
    if (kelimeler.empty()) {
        return "";
    }
    std::string onek = kelimeler[0];
    for (std::size_t i = 1; i < kelimeler.size(); ++i) {
        std::size_t j = 0;
        while (j < onek.size() && j < kelimeler[i].size() && onek[j] == kelimeler[i][j]) {
            ++j;
        }
        onek.resize(j);                  // sadece eşleşen kısım kalsın
        if (onek.empty()) {
            break;                       // ortak önek yok: devam etmeye gerek yok
        }
    }
    return onek;
}

// Yöntem 2: Alfabetik sıralayınca en farklı iki kelime BAŞTA ve SONDA olur;
// ortak önek, ilk ile son kelimenin ortak önekidir. O(n log n * L) (sıralama), ama kod çok kısa.
std::string ortakOnekSirala(std::vector<std::string> kelimeler) {
    if (kelimeler.empty()) {
        return "";
    }
    std::sort(kelimeler.begin(), kelimeler.end());
    const std::string& ilk = kelimeler.front();
    const std::string& son = kelimeler.back();
    std::size_t j = 0;
    while (j < ilk.size() && j < son.size() && ilk[j] == son[j]) {
        ++j;
    }
    return ilk.substr(0, j);
}

int main() {
    std::vector<std::vector<std::string>> testler = {
        {"flower", "flow", "flight"},
        {"dog", "racecar", "car"},
        {"interview", "internet", "internal", "interval"},
        {"a"},
        {"abc", "abc"},
        {"", "abc"},
        {"prefix", "pre", "prefecture"},
        {}};
    for (const auto& t : testler) {
        std::cout << "{";
        for (std::size_t i = 0; i < t.size(); ++i) {
            std::cout << "\"" << t[i] << "\"" << (i + 1 < t.size() ? ", " : "");
        }
        std::cout << "} -> \"" << ortakOnek(t) << "\"  (siralama yontemi: \"" << ortakOnekSirala(t) << "\")\n";
    }
    return 0;
}
