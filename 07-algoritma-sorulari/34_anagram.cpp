// Konu: Anagram kontrolü (aynı harflerden oluşan iki kelime: listen / silent)
// Ne gösteriyor: Sıralayarak (O(n log n)) ve harf sayaçlarıyla (O(n)) çözümü.
// Neden önemli: Çok sorulur; "daha hızlı çözümü var mı?" takip sorusu sayaç yöntemini ister.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 34_anagram 34_anagram.cpp

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

// Her iki stringi sıralayıp karşılaştırır. O(n log n).
bool anagramSirala(std::string a, std::string b) {
    if (a.size() != b.size()) {
        return false;                 // uzunluk farklıysa olamaz
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return a == b;
}

// Harf sayaçları: a için artır, b için azalt; hepsi 0 ise anagram. O(n), O(1) bellek (26 harf).
bool anagramSayac(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) {
        return false;
    }
    int say[26] = {};
    for (std::size_t i = 0; i < a.size(); ++i) {
        ++say[std::tolower(static_cast<unsigned char>(a[i])) - 'a'];
        --say[std::tolower(static_cast<unsigned char>(b[i])) - 'a'];
    }
    for (int s : say) {
        if (s != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    struct Test { std::string a; std::string b; };
    for (Test t : {Test{"listen", "silent"}, Test{"hello", "world"}, Test{"abc", "ab"}, Test{"", ""}, Test{"Listen", "Silent"}}) {
        std::cout << "\"" << t.a << "\" ve \"" << t.b << "\": siralayarak = " << anagramSirala(t.a, t.b)
                  << ", sayacla = " << anagramSayac(t.a, t.b) << "\n";
    }
    std::cout << "NOT: sayac yontemi buyuk/kucuk harfi esitler, siralama yontemi esitlemez (Listen/Silent).\n";
    return 0;
}
