// Konu: String'i büyük harfe çevirmek
// Ne gösteriyor: ASCII farkıyla ('a' - 'A' = 32) elle çevirmeyi ve std::toupper ile aynı işi.
// Neden önemli: Karakter kodlarını (ASCII) bilmeyi ölçer; Türkçe karakterlerin neden sorun olduğunu gösterir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 35_buyuk_harfe_cevir 35_buyuk_harfe_cevir.cpp

#include <cctype>
#include <iostream>
#include <string>

// ASCII'de küçük harf = büyük harf + 32. Yalnızca 'a'..'z' aralığını çeviriyoruz.
std::string buyukHarfElle(std::string s) {
    for (char& c : s) {
        if (c >= 'a' && c <= 'z') {
            c = static_cast<char>(c - 'a' + 'A');
        }
    }
    return s;
}

std::string buyukHarfKutuphane(std::string s) {
    for (char& c : s) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return s;
}

int main() {
    for (std::string s : {"merhaba Dunya 123", "abc XYZ", "", "c++ ogren"}) {
        std::cout << "\"" << s << "\" -> elle: \"" << buyukHarfElle(s) << "\", toupper: \"" << buyukHarfKutuphane(s) << "\"\n";
    }
    std::cout << "NOT: 'a' - 'A' = " << ('a' - 'A') << ". Turkce harfler (c, g, i, o, s, u) ASCII disindadir, bu yontemle cevrilmez.\n";
    return 0;
}
