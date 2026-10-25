// Konu: String'deki ilk tekrar etmeyen karakter
// Ne gösteriyor: İki geçişle çözümü: önce frekans say, sonra baştan tara; ilk sayısı 1 olanı bul.
// Neden önemli: Frekans tablosu kalıbının sık sorulan uygulaması (swiss -> w).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 37_ilk_tekrar_etmeyen_karakter 37_ilk_tekrar_etmeyen_karakter.cpp

#include <cstddef>
#include <iostream>
#include <string>

// O(n) zaman, O(1) bellek (256 sabit boyutlu sayaç). Bulamazsa -1 döner.
int ilkTekrarEtmeyen(const std::string& s) {
    int say[256] = {};
    for (char c : s) {
        ++say[static_cast<unsigned char>(c)];       // char negatif olabilir: unsigned char'a çevir
    }
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (say[static_cast<unsigned char>(s[i])] == 1) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {
    for (std::string s : {"swiss", "leetcode", "aabb", "", "x", "aabbcdd"}) {
        int i = ilkTekrarEtmeyen(s);
        std::cout << "\"" << s << "\" -> ";
        if (i >= 0) {
            std::cout << "'" << s[static_cast<std::size_t>(i)] << "' (indeks " << i << ")\n";
        } else {
            std::cout << "yok\n";
        }
    }
    return 0;
}
