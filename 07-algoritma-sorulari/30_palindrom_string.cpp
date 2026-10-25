// Konu: Palindrom kontrolü (string)
// Ne gösteriyor: Baştan ve sondan karşılaştırmayı; ve harf olmayanları/büyük-küçük farkını yok sayan "gevşek" sürümü.
// Neden önemli: Çok sorulur; gevşek sürüm ("A man, a plan, a canal: Panama") takip sorusu olarak gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 30_palindrom_string 30_palindrom_string.cpp

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

// Birebir karşılaştırır. O(n) zaman, O(1) bellek. Boş string palindromdur.
bool palindromMu(const std::string& s) {
    if (s.empty()) {
        return true;
    }
    std::size_t sol = 0;
    std::size_t sag = s.size() - 1;
    while (sol < sag) {
        if (s[sol] != s[sag]) {
            return false;
        }
        ++sol;
        --sag;
    }
    return true;
}

// Harf/rakam olmayanları atlar, büyük-küçük harf farkını yok sayar.
bool palindromGevsek(const std::string& s) {
    if (s.empty()) {
        return true;
    }
    std::size_t sol = 0;
    std::size_t sag = s.size() - 1;
    while (sol < sag) {
        while (sol < sag && !std::isalnum(static_cast<unsigned char>(s[sol]))) {
            ++sol;
        }
        while (sol < sag && !std::isalnum(static_cast<unsigned char>(s[sag]))) {
            --sag;
        }
        if (std::tolower(static_cast<unsigned char>(s[sol])) != std::tolower(static_cast<unsigned char>(s[sag]))) {
            return false;
        }
        ++sol;
        --sag;
    }
    return true;
}

int main() {
    for (std::string s : {"radar", "level", "hello", "ab", "", "A man, a plan, a canal: Panama", "No lemon, no melon"}) {
        std::cout << "\"" << s << "\": birebir = " << palindromMu(s) << ", gevsek = " << palindromGevsek(s) << "\n";
    }
    return 0;
}
