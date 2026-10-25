// Konu: İkili arama (binary search)
// Ne gösteriyor: SIRALI dizide her adımda aralığı yarıya bölerek O(log n)'de aramayı; adım sayısını.
// Neden önemli: Mülakatın en meşhur algoritma sorusu; "dizi sıralı olmalı" şartı ve orta indeks hesabı sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 20_ikili_arama 20_ikili_arama.cpp

#include <iostream>
#include <vector>

// Dizi SIRALI olmak zorundadır. Bulursa indeksi, bulamazsa -1 döner. adim: kaç karşılaştırma yapıldı.
int ikiliArama(const std::vector<int>& v, int aranan, int& adim) {
    int sol = 0;
    int sag = static_cast<int>(v.size()) - 1;
    adim = 0;
    while (sol <= sag) {
        ++adim;
        int orta = sol + (sag - sol) / 2;     // (sol + sag) / 2 büyük dizilerde taşabilir
        if (v[static_cast<std::size_t>(orta)] == aranan) {
            return orta;
        }
        if (v[static_cast<std::size_t>(orta)] < aranan) {
            sol = orta + 1;                   // aranan sağ yarıda
        } else {
            sag = orta - 1;                   // aranan sol yarıda
        }
    }
    return -1;
}

int main() {
    std::vector<int> v = {1, 3, 5, 7, 9, 11, 13, 15};
    for (int aranan : {7, 1, 15, 4, 100}) {
        int adim = 0;
        int sonuc = ikiliArama(v, aranan, adim);
        std::cout << aranan << (sonuc >= 0 ? " bulundu, indeks = " : " bulunamadi ") << (sonuc >= 0 ? std::to_string(sonuc) : "")
                  << "  (adim: " << adim << ")\n";
    }

    std::vector<int> buyuk;
    for (int i = 1; i <= 1000; ++i) {
        buyuk.push_back(i);
    }
    int adim = 0;
    ikiliArama(buyuk, 777, adim);
    std::cout << "1000 elemanli dizide 777: " << adim << " adimda (dogrusal aramada en cok 1000)\n";

    int bosAdim = 0;
    std::cout << "bos dizi: " << ikiliArama({}, 5, bosAdim) << "\n";
    return 0;
}
