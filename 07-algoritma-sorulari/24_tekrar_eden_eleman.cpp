// Konu: Dizide tekrar eden eleman var mı?
// Ne gösteriyor: Sıralayıp komşuları karşılaştırmayı (O(n log n)) ve unordered_set ile tek geçişte çözmeyi (O(n) ortalama).
// Neden önemli: Zaman/bellek takası (trade-off) sorusunun güzel bir örneği: daha hızlı çözüm daha fazla bellek ister.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 24_tekrar_eden_eleman 24_tekrar_eden_eleman.cpp

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <unordered_set>
#include <vector>

// Kopya üzerinde sıralar (orijinali bozmaz). O(n log n) zaman, O(n) bellek (kopya).
bool tekrarVarSirala(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] == v[i - 1]) {
            return true;
        }
    }
    return false;
}

// O(n) ortalama zaman, O(n) bellek. insert: eleman zaten varsa second false döner.
bool tekrarVarKume(const std::vector<int>& v) {
    std::unordered_set<int> gorulen;
    for (int x : v) {
        if (!gorulen.insert(x).second) {
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<std::vector<int>> testler = {{1, 2, 3, 4}, {1, 2, 3, 1}, {5, 5}, {7}, {}};
    for (const auto& v : testler) {
        std::cout << "eleman sayisi " << v.size() << ": siralayarak = " << tekrarVarSirala(v)
                  << ", kume ile = " << tekrarVarKume(v) << "\n";
    }
    return 0;
}
