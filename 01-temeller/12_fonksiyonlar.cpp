// Konu: Fonksiyonlar: geçirme türleri, overloading, varsayılan argüman, inline ve özyineleme
// Ne gösteriyor: Değerle/referansla/pointer ile geçirmeyi, aşırı yüklemenin hangi fonksiyonu seçtiğini ve varsayılan argümanı.
// Neden önemli: "Overloading nedir?", "varsayılan argümanın kuralları?" ve "referans mı pointer mı?" mülakatta sık sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 12_fonksiyonlar 12_fonksiyonlar.cpp

#include <iostream>
#include <string>

// ------------------------------------------------------------ 1) Geçirme türleri
void artirDeger(int x) { x++; }                 // kopya: orijinal değişmez
void artirRef(int& x) { x++; }                  // referans: orijinal değişir
void artirPtr(int* x) { if (x != nullptr) { (*x)++; } }   // pointer: nullptr kontrolü gerekir

// ------------------------------------------------------------ 2) Overloading (aşırı yükleme)
// Aynı isim, FARKLI PARAMETRE LİSTESİ. (Sadece dönüş tipi farklıysa overload OLMAZ.)
int topla(int a, int b) {
    std::cout << "  topla(int, int) ";
    return a + b;
}
double topla(double a, double b) {
    std::cout << "  topla(double, double) ";
    return a + b;
}
std::string topla(const std::string& a, const std::string& b) {
    std::cout << "  topla(string, string) ";
    return a + b;
}

// const olan ve olmayan referans ayrı overload sayılır.
void yaz(int& x) { std::cout << "  yaz(int&): degistirilebilir nesne " << x << "\n"; }
void yaz(const int& x) { std::cout << "  yaz(const int&): sabit/gecici deger " << x << "\n"; }

// --------------------------------------- 3) Varsayılan argüman
// Varsayılan değerler SAĞDAN SOLA doldurulur: varsayılanı olmayan parametre, olanın SOLUNDA olmalıdır.
void kayit(const std::string& mesaj, int seviye = 1, bool zaman = false) {
    std::cout << "  [seviye=" << seviye << " zaman=" << zaman << "] " << mesaj << "\n";
}

// ------------------------------------------------------------ 4) inline
// Modern C++'ta inline "derleyiciye ipucu"dan çok, başlık dosyasında tanımlanabilmeyi (ODR) sağlar.
inline int kare(int x) { return x * x; }

// ------------------------------------------------------------ 5) Özyineleme (recursion)
long long faktoriyel(int n) {
    if (n <= 1) {            // taban durum (base case): olmazsa sonsuz özyineleme = stack overflow
        return 1;
    }
    return n * faktoriyel(n - 1);
}

int main() {
    // 1) Geçirme türleri
    std::cout << "--- 1) Gecirme turleri ---\n";
    int s = 5;
    artirDeger(s);
    std::cout << "artirDeger sonrasi s = " << s << "\n";
    artirRef(s);
    std::cout << "artirRef   sonrasi s = " << s << "\n";
    artirPtr(&s);
    std::cout << "artirPtr   sonrasi s = " << s << "\n";
    artirPtr(nullptr);   // güvenli: fonksiyon içinde kontrol var
    std::cout << "artirPtr(nullptr) cokmedi\n";

    // 2) Overloading
    std::cout << "\n--- 2) Overloading ---\n";
    std::cout << "= " << topla(1, 2) << "\n";
    std::cout << "= " << topla(1.5, 2.5) << "\n";
    std::cout << "= " << topla(std::string("ab"), std::string("cd")) << "\n";
    // topla(1, 2.5);   // HATA: ambiguous (int,int) mi (double,double) mı? İkisi de bir dönüşüm gerektirir.

    int a = 7;
    const int c = 3;
    yaz(a);      // int&   (değişken, değiştirilebilir)
    yaz(c);      // const int&
    yaz(42);     // const int& (geçici değer T&'ye bağlanamaz)

    // 3) Varsayılan argüman
    std::cout << "\n--- 3) Varsayilan arguman ---\n";
    kayit("sadece mesaj");
    kayit("seviye verildi", 2);
    kayit("hepsi verildi", 3, true);

    // 4) inline
    std::cout << "\n--- 4) inline ---\n";
    std::cout << "kare(9) = " << kare(9) << "\n";

    // 5) Özyineleme
    std::cout << "\n--- 5) Ozyineleme ---\n";
    std::cout << "faktoriyel(5)  = " << faktoriyel(5) << "\n";
    std::cout << "faktoriyel(20) = " << faktoriyel(20) << "\n";

    return 0;
}
