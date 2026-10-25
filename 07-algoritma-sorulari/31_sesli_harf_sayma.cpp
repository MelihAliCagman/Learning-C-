// Konu: Bir string'deki sesli harfleri saymak
// Ne gösteriyor: Karakter karakter gezmeyi, büyük/küçük harfi eşitlemeyi (tolower) ve unsigned char dönüşümünü.
// Neden önemli: Basit string döngüsü sorusu; <cctype> fonksiyonlarını doğru kullanmayı ölçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 31_sesli_harf_sayma 31_sesli_harf_sayma.cpp

#include <cctype>
#include <iostream>
#include <string>

bool sesliMi(char c) {
    // tolower/isalpha gibi fonksiyonlar unsigned char ister; negatif char değerleri tanımsız davranıştır.
    char k = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return k == 'a' || k == 'e' || k == 'i' || k == 'o' || k == 'u';
}

int sesliSay(const std::string& s) {
    int sayac = 0;
    for (char c : s) {
        if (sesliMi(c)) {
            ++sayac;
        }
    }
    return sayac;
}

int main() {
    for (std::string s : {"Merhaba Dunya", "rhythm", "AEIOU", "", "Programming 123"}) {
        std::cout << "\"" << s << "\" -> sesli harf sayisi = " << sesliSay(s) << "\n";
    }
    return 0;
}
