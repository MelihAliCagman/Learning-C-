// Konu: const& parametre: kopyasız ve güvenli okuma
// Ne gösteriyor: Aynı nesneyi üç farklı biçimde (değerle, referansla, const referansla) fonksiyona geçiriyor.
// Neden önemli: Büyük nesneleri gereksiz kopyalamamak ve fonksiyonun orijinali bozmasını önlemek için her yerde kullanılır.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 03_const_ref 03_const_ref.cpp

#include <iostream>
#include <string>

// Kopyalandığında ekrana "KOPYA!" yazan küçük bir sınıf.
// (Kopya constructor'ı henüz görmedik; şimdilik sadece "kopya olunca bu satır çalışır" diye bil.)
struct Tracker {
    std::string name;

    Tracker(const std::string& n) : name(n) {}
    Tracker(const Tracker& other) : name(other.name) {
        std::cout << "  KOPYA! (" << name << ")\n";
    }
};

// (1) Değerle: her çağrıda kopya oluşur.
void showByValue(Tracker t) {
    std::cout << "  okundu: " << t.name << "\n";
}

// (2) Referansla: kopya yok ama fonksiyon orijinali değiştirebilir.
void showByRef(Tracker& t) {
    std::cout << "  okundu: " << t.name << "\n";
}

// (3) const referansla: kopya yok ve değiştirmek de yasak.
void showByConstRef(const Tracker& t) {
    std::cout << "  okundu: " << t.name << "\n";
}

int main() {
    Tracker original("sensor-1");

    std::cout << "(1) showByValue:\n";
    showByValue(original);

    std::cout << "(2) showByRef:\n";
    showByRef(original);

    std::cout << "(3) showByConstRef:\n";
    showByConstRef(original); // Kopya yazmaz ("KOPYA!" çıkmaz).

    // Deney A: showByConstRef'in içine  t.name = "degisti";  yaz. Derleyici ne diyor?
    // Deney B: showByRef(Tracker("gecici"));  yaz. Derleyici ne diyor? Aynısını showByConstRef ile dene.

    return 0;
}
