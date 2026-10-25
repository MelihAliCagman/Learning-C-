// Konu: Bir string'i ters çevirmek
// Ne gösteriyor: İki indeksle elle ters çevirmeyi ve std::reverse ile aynı işi; boş/tek karakter kenar durumlarını.
// Neden önemli: En klasik canlı kodlama sorusu; "iki işaretçi" tekniğinin temeli.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 29_string_ters_cevir 29_string_ters_cevir.cpp

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

// Değerle alıyoruz: kopya üzerinde çalışıp döndürüyoruz, orijinal bozulmuyor. O(n) zaman, O(1) ek bellek.
std::string tersCevir(std::string s) {
    if (s.size() < 2) {                   // boş ya da tek karakter; s.size() - 1 boşta taşardı
        return s;
    }
    std::size_t sol = 0;
    std::size_t sag = s.size() - 1;
    while (sol < sag) {
        std::swap(s[sol], s[sag]);
        ++sol;
        --sag;
    }
    return s;
}

int main() {
    for (std::string s : {"merhaba", "ab", "a", "", "level", "C++ ogren"}) {
        std::string kutuphane = s;
        std::reverse(kutuphane.begin(), kutuphane.end());
        std::cout << "\"" << s << "\" -> \"" << tersCevir(s) << "\"  (std::reverse: \"" << kutuphane << "\")\n";
    }
    return 0;
}
