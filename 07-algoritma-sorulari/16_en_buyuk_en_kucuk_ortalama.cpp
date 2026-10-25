// Konu: Dizide en büyük, en küçük eleman ve ortalama
// Ne gösteriyor: Tek döngüde bulmayı, boş dizi kenar durumunu ve toplamın taşmasını önlemeyi.
// Neden önemli: Mülakatın en temel dizi sorusu; "boş dizi gelirse ne olur?" mutlaka sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 16_en_buyuk_en_kucuk_ortalama 16_en_buyuk_en_kucuk_ortalama.cpp

#include <iostream>
#include <vector>

// Boş dizide sonuç olmaz: false döndürüyoruz (v[0] okumak tanımsız davranış olurdu).
bool enBuyuk(const std::vector<int>& v, int& sonuc) {
    if (v.empty()) {
        return false;
    }
    sonuc = v[0];                  // 0 ile başlatmak YANLIŞ: tüm elemanlar negatif olabilir
    for (int x : v) {
        if (x > sonuc) {
            sonuc = x;
        }
    }
    return true;
}

bool enKucuk(const std::vector<int>& v, int& sonuc) {
    if (v.empty()) {
        return false;
    }
    sonuc = v[0];
    for (int x : v) {
        if (x < sonuc) {
            sonuc = x;
        }
    }
    return true;
}

bool ortalama(const std::vector<int>& v, double& sonuc) {
    if (v.empty()) {
        return false;
    }
    long long toplam = 0;          // int toplam taşabilir
    for (int x : v) {
        toplam += x;
    }
    sonuc = static_cast<double>(toplam) / static_cast<double>(v.size());   // tamsayı bölme ondalığı atardı
    return true;
}

int main() {
    std::vector<std::vector<int>> testler = {{3, -1, 7, 7, 0}, {-5, -2, -9}, {42}, {}};
    for (const auto& v : testler) {
        int b = 0, k = 0;
        double o = 0.0;
        if (enBuyuk(v, b) && enKucuk(v, k) && ortalama(v, o)) {
            std::cout << "eleman: " << v.size() << "  max = " << b << "  min = " << k << "  ortalama = " << o << "\n";
        } else {
            std::cout << "bos dizi: sonuc yok\n";
        }
    }
    return 0;
}
