// Konu: Harf frekansı (her harf kaç kez geçiyor?)
// Ne gösteriyor: 26 elemanlı sayaç dizisini ve 'c' - 'a' ile harfi indekse çevirmeyi.
// Neden önemli: "Frekans tablosu" kalıbının en basit hâli; anagram ve kelime sıklığı sorularının temeli.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 32_harf_frekansi 32_harf_frekansi.cpp

#include <cctype>
#include <iostream>
#include <string>

int main() {
    for (std::string s : {"merhaba", "Hello World", ""}) {
        int say[26] = {};                       // hepsi 0 ile başlar
        for (char c : s) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char k = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                ++say[k - 'a'];                 // 'a' -> 0, 'b' -> 1, ... 'z' -> 25
            }
        }
        std::cout << "\"" << s << "\": ";
        for (int i = 0; i < 26; ++i) {
            if (say[i] > 0) {
                std::cout << static_cast<char>('a' + i) << "=" << say[i] << " ";
            }
        }
        std::cout << "\n";
    }
    return 0;
}
