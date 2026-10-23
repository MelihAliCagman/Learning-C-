// Konu: Dizi ve pointer ilişkisi, pointer aritmetiği, dizinin fonksiyona geçmesi (decay)
// Ne gösteriyor: Dizi adının ilk elemanın adresine dönüşmesini, p + 1'in kaç bayt ilerlediğini ve sizeof tuzağını.
// Neden önemli: C ve C++ mülakatlarının klasiği; arr[i] ile *(arr + i) aynı şeydir, dizi sınırı aşmak tanımsız davranıştır.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 13_dizi_pointer 13_dizi_pointer.cpp

#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>

// Dizi bir fonksiyona geçerken İLK ELEMANIN ADRESİNE dönüşür (array-to-pointer decay).
// Boyut bilgisi kaybolur: fonksiyon sadece bir pointer görür, bu yüzden boyut AYRI parametre olarak verilir.
void boyutuGoster(const int* a) {
    std::cout << "  fonksiyon icinde sizeof(a) = " << sizeof(a) << " (dizi degil, sadece pointer boyutu)\n";
}

int topla(const int* a, std::size_t n) {
    int toplam = 0;
    for (std::size_t i = 0; i < n; ++i) {
        toplam += a[i];
    }
    return toplam;
}

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // 1) Dizi ve boyut
    std::cout << "--- 1) Dizi ve boyut ---\n";
    std::cout << "sizeof(arr)         = " << sizeof(arr) << " bayt (5 eleman x 4 bayt)\n";
    std::cout << "eleman sayisi       = " << sizeof(arr) / sizeof(arr[0]) << "\n";
    std::cout << "std::size(arr)      = " << std::size(arr) << "\n";
    boyutuGoster(arr);

    // 2) Dizi adı = ilk elemanın adresi
    std::cout << "\n--- 2) Dizi adi ve adres ---\n";
    int* p = arr;   // arr, &arr[0]'a dönüşür
    std::cout << "arr == &arr[0] ? " << (arr == &arr[0]) << "\n";
    std::cout << "*p = " << *p << ", p[2] = " << p[2] << ", *(p + 2) = " << *(p + 2) << "\n";
    std::cout << "arr[3] = " << arr[3] << ", *(arr + 3) = " << *(arr + 3) << "  (ayni sey)\n";

    // 3) Pointer aritmetiği: p + 1, bir ELEMAN ilerletir (bayt değil)
    std::cout << "\n--- 3) Pointer aritmetigi ---\n";
    const char* b0 = reinterpret_cast<const char*>(p);
    const char* b1 = reinterpret_cast<const char*>(p + 1);
    std::cout << "p ile p + 1 arasindaki bayt farki = " << (b1 - b0) << "  (sizeof(int))\n";
    int* son = arr + 4;
    std::cout << "son - p (eleman sayisi farki) = " << (son - p) << "\n";

    std::cout << "pointer ile dolasma: ";
    for (int* q = arr; q != arr + 5; ++q) {
        std::cout << *q << " ";
    }
    std::cout << "\n";

    // 4) &arr ile arr farkı (klasik mülakat tuzağı)
    std::cout << "\n--- 4) arr ile &arr ---\n";
    const char* a0 = reinterpret_cast<const char*>(arr);
    const char* a1 = reinterpret_cast<const char*>(arr + 1);       // bir int ilerler
    const char* a2 = reinterpret_cast<const char*>(&arr + 1);      // BUTUN DIZI kadar ilerler
    std::cout << "arr + 1  ilerleme = " << (a1 - a0) << " bayt\n";
    std::cout << "&arr + 1 ilerleme = " << (a2 - a0) << " bayt\n";

    // 5) Diziyi fonksiyona geçmek
    std::cout << "\n--- 5) Diziyi fonksiyona gecmek ---\n";
    std::cout << "topla(arr, 5) = " << topla(arr, 5) << "\n";
    std::cout << "topla(arr + 2, 3) = " << topla(arr + 2, 3) << "  (ortadan baslayarak: 30+40+50)\n";

    // 6) İki boyutlu dizi: bellekte satır satır, tek parça
    std::cout << "\n--- 6) Iki boyutlu dizi ---\n";
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    std::cout << "sizeof(m) = " << sizeof(m) << ", sizeof(m[0]) = " << sizeof(m[0]) << " (bir satir)\n";
    std::cout << "m[1][2] = " << m[1][2] << ", *(*(m + 1) + 2) = " << *(*(m + 1) + 2) << "\n";
    const int* duz = &m[0][0];
    std::cout << "duz dolasma: ";
    for (int i = 0; i < 6; ++i) {
        std::cout << duz[i] << " ";
    }
    std::cout << "\n";

    // 7) Sınır dışı erişim: arr[5], arr[-1] TANIMSIZ DAVRANIŞTIR (derleyici uyarmayabilir, çalıştırma!)
    //    Güvenli alternatif: std::array ve .at() sınır dışında istisna fırlatır.
    std::cout << "\n--- 7) Sinir kontrolu ---\n";
    std::array<int, 3> guvenli = {1, 2, 3};
    std::cout << "guvenli.at(1) = " << guvenli.at(1) << "\n";
    try {
        int deger = guvenli.at(5);   // sınır dışı: istisna fırlatır
        std::cout << "guvenli.at(5) = " << deger << "\n";
    } catch (const std::out_of_range&) {
        std::cout << "guvenli.at(5) -> out_of_range istisnasi yakalandi (arr[5] ise sessizce tanimsiz davranis olurdu)\n";
    }

    return 0;
}
