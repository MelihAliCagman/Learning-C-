// Konu: İki toplam (two sum): toplamı hedef olan iki elemanın indeksleri
// Ne gösteriyor: İç içe iki döngüyle O(n^2) çözümü ve unordered_map ile O(n) çözümü.
// Neden önemli: Dünyanın en çok sorulan mülakat sorusu; zaman/bellek takasını anlatmak için ideal.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 28_iki_toplam 28_iki_toplam.cpp

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>

// O(n^2) zaman, O(1) bellek: her çifti dene.
bool ikiToplamYavas(const std::vector<int>& v, int hedef, std::size_t& a, std::size_t& b) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        for (std::size_t j = i + 1; j < v.size(); ++j) {
            if (v[i] + v[j] == hedef) {
                a = i;
                b = j;
                return true;
            }
        }
    }
    return false;
}

// O(n) ortalama zaman, O(n) bellek: eşini ("hedef - x") daha önce gördün mü?
bool ikiToplamHizli(const std::vector<int>& v, int hedef, std::size_t& a, std::size_t& b) {
    std::unordered_map<int, std::size_t> gorulen;      // değer -> indeks
    for (std::size_t i = 0; i < v.size(); ++i) {
        auto bulunan = gorulen.find(hedef - v[i]);
        if (bulunan != gorulen.end()) {
            a = bulunan->second;
            b = i;
            return true;
        }
        gorulen[v[i]] = i;
    }
    return false;
}

int main() {
    struct Test { std::vector<int> v; int hedef; };
    for (Test t : {Test{{2, 7, 11, 15}, 9}, Test{{3, 2, 4}, 6}, Test{{3, 3}, 6}, Test{{1, 2, 3}, 100}, Test{{}, 5}}) {
        std::size_t a = 0, b = 0;
        std::size_t c = 0, d = 0;
        bool yavas = ikiToplamYavas(t.v, t.hedef, a, b);
        bool hizli = ikiToplamHizli(t.v, t.hedef, c, d);
        std::cout << "hedef " << t.hedef << ": ";
        if (yavas && hizli) {
            std::cout << "indeksler (" << a << ", " << b << ") ve (" << c << ", " << d << ")\n";
        } else {
            std::cout << "cift yok\n";
        }
    }
    return 0;
}
