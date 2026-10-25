// Konu: Sayısal algoritma soruları: en büyük/en küçük/ortalama, faktöriyel, Fibonacci, asal kontrolü
// Ne gösteriyor: Her sorunun döngülü ve özyineli çözümünü, kenar durumları (boş girdi, taşma) ve zaman karmaşıklığı farkını.
// Neden önemli: Canlı kodlama mülakatının klasikleri; çözümden çok kenar durumları ve karmaşıklığı anlatabilmek puan getirir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 21_sayisal_problemler 21_sayisal_problemler.cpp

#include <cstdint>
#include <iostream>
#include <vector>

// ---------------------------------------------------------------- 1) En büyük, en küçük, ortalama
// Tek geçişte (O(n)) üçünü birden hesaplar. Boş vektör için false döner (kenar durum).
bool istatistik(const std::vector<int>& v, int& enKucuk, int& enBuyuk, double& ortalama) {
    if (v.empty()) {
        return false;
    }
    enKucuk = v[0];
    enBuyuk = v[0];
    long long toplam = 0;          // int toplam taşabilir; long long kullanıyoruz
    for (int x : v) {
        if (x < enKucuk) enKucuk = x;
        if (x > enBuyuk) enBuyuk = x;
        toplam += x;
    }
    ortalama = static_cast<double>(toplam) / static_cast<double>(v.size());
    return true;
}

// ---------------------------------------------------------------- 2) Faktöriyel
// 20! uint64_t'ye sığar (2432902008176640000), 21! sığmaz. Taşmayı çağırana bildiriyoruz.
bool faktoriyel(int n, std::uint64_t& sonuc) {
    if (n < 0 || n > 20) {
        return false;
    }
    sonuc = 1;
    for (int i = 2; i <= n; ++i) {
        sonuc *= static_cast<std::uint64_t>(i);
    }
    return true;
}

// Özyineli sürüm (taban durum: n <= 1). Stack kullanır, n büyükse stack overflow riski.
std::uint64_t faktoriyelOzyineli(int n) {
    if (n <= 1) {
        return 1;
    }
    return static_cast<std::uint64_t>(n) * faktoriyelOzyineli(n - 1);
}

// ---------------------------------------------------------------- 3) Fibonacci
// F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
long long cagriSayisi = 0;   // özyineli sürümün kaç çağrı yaptığını saymak için

std::uint64_t fibOzyineli(int n) {            // O(2^n): aynı alt problemler tekrar tekrar hesaplanır
    ++cagriSayisi;
    if (n < 2) {
        return static_cast<std::uint64_t>(n);
    }
    return fibOzyineli(n - 1) + fibOzyineli(n - 2);
}

std::uint64_t fibDongu(int n) {               // O(n) zaman, O(1) bellek
    if (n < 2) {
        return static_cast<std::uint64_t>(n);
    }
    std::uint64_t onceki = 0;
    std::uint64_t simdiki = 1;
    for (int i = 2; i <= n; ++i) {
        std::uint64_t sonraki = onceki + simdiki;
        onceki = simdiki;
        simdiki = sonraki;
    }
    return simdiki;
}

std::uint64_t fibMemo(int n, std::vector<std::uint64_t>& hafiza) {   // O(n): özyineli ama sonuçları saklar
    if (n < 2) {
        return static_cast<std::uint64_t>(n);
    }
    if (hafiza[static_cast<std::size_t>(n)] != 0) {
        return hafiza[static_cast<std::size_t>(n)];
    }
    hafiza[static_cast<std::size_t>(n)] = fibMemo(n - 1, hafiza) + fibMemo(n - 2, hafiza);
    return hafiza[static_cast<std::size_t>(n)];
}

// ---------------------------------------------------------------- 4) Asal kontrolü
// n'in bölenleri sqrt(n)'e kadar bakmak yeter: O(sqrt(n)). i * i taşmasın diye i <= n / i yazıyoruz.
bool asalMi(long long n) {
    if (n < 2) {
        return false;
    }
    if (n < 4) {
        return true;             // 2 ve 3
    }
    if (n % 2 == 0) {
        return false;
    }
    for (long long i = 3; i <= n / i; i += 2) {   // sadece tek sayılar
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cout << "--- 1) istatistik ---\n";
    std::vector<std::vector<int>> testler = {{3, -1, 7, 7, 0}, {42}, {}};
    for (const auto& v : testler) {
        int kucuk = 0, buyuk = 0;
        double ort = 0.0;
        if (istatistik(v, kucuk, buyuk, ort)) {
            std::cout << "  eleman sayisi " << v.size() << ": min = " << kucuk << ", max = " << buyuk << ", ortalama = " << ort << "\n";
        } else {
            std::cout << "  bos vektor: istatistik yok\n";
        }
    }

    std::cout << "\n--- 2) faktoriyel ---\n";
    for (int n : {0, 1, 5, 10, 20, 21, -3}) {
        std::uint64_t f = 0;
        if (faktoriyel(n, f)) {
            std::cout << "  " << n << "! = " << f << "\n";
        } else {
            std::cout << "  " << n << "! hesaplanamadi (negatif veya uint64_t'ye sigmaz)\n";
        }
    }
    std::cout << "  ozyineli 10! = " << faktoriyelOzyineli(10) << "\n";

    std::cout << "\n--- 3) Fibonacci ---\n";
    std::cout << "  dongu: ";
    for (int i = 0; i <= 10; ++i) {
        std::cout << fibDongu(i) << " ";
    }
    std::cout << "\n  fibDongu(50) = " << fibDongu(50) << ", fibDongu(93) = " << fibDongu(93) << "  (94'te uint64_t tasar)\n";

    cagriSayisi = 0;
    std::uint64_t fo = fibOzyineli(30);
    std::cout << "  fibOzyineli(30) = " << fo << ", cagri sayisi = " << cagriSayisi << "  (O(2^n))\n";

    std::vector<std::uint64_t> hafiza(51, 0);
    std::cout << "  fibMemo(50)     = " << fibMemo(50, hafiza) << "  (hafizali, O(n))\n";

    std::cout << "\n--- 4) asal ---\n";
    for (long long n : {0LL, 1LL, 2LL, 3LL, 4LL, 17LL, 25LL, 97LL, 7919LL, 1000000007LL, 1000000008LL}) {
        std::cout << "  " << n << (asalMi(n) ? " asal" : " asal degil") << "\n";
    }
    std::cout << "  asal sayilar (<= 50): ";
    for (int n = 2; n <= 50; ++n) {
        if (asalMi(n)) {
            std::cout << n << " ";
        }
    }
    std::cout << "\n";

    return 0;
}
