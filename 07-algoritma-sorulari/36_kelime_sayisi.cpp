// Konu: Bir cümledeki kelime sayısı
// Ne gösteriyor: Boşluktan harfe geçişleri sayarak kelimeleri bulmayı; baştaki/sondaki/art arda boşluk kenar durumlarını.
// Neden önemli: "Boşluk sayısı + 1" gibi yaygın yanlışı yakalamayı ölçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 36_kelime_sayisi 36_kelime_sayisi.cpp

#include <cctype>
#include <iostream>
#include <string>

// Boşluk olmayan bir karaktere, bir önceki karakter boşluktaysa (veya başındaysak) yeni bir kelime başlar.
int kelimeSayisi(const std::string& s) {
    int sayac = 0;
    bool kelimedeMi = false;
    for (char c : s) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            kelimedeMi = false;
        } else if (!kelimedeMi) {
            kelimedeMi = true;
            ++sayac;
        }
    }
    return sayac;
}

int main() {
    for (std::string s : {"merhaba dunya", "  merhaba   dunya ben ", "tek", "", "     "}) {
        std::cout << "\"" << s << "\" -> " << kelimeSayisi(s) << " kelime\n";
    }
    std::cout << "NOT: bosluk sayisi + 1 formulu bastaki/sondaki/art arda bosluklarda YANLIS sonuc verir.\n";
    return 0;
}
