// Konu: EBOB (en büyük ortak bölen) ve EKOK (en küçük ortak kat)
// Ne gösteriyor: Öklid algoritmasını ve EKOK'u EBOB'dan hesaplamayı.
// Neden önemli: Tarihin en eski algoritmalarından; kısa, zarif ve sık sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 08_ebob_ekok 08_ebob_ekok.cpp

#include <iostream>

// Öklid: ebob(a, b) = ebob(b, a % b); b sıfır olunca sonuç a'dır.
int ebob(int a, int b) {
    while (b != 0) {
        int kalan = a % b;
        a = b;
        b = kalan;
    }
    return a;
}

// EKOK = a * b / EBOB. Önce bölüp sonra çarpmak taşmayı azaltır.
long long ekok(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return static_cast<long long>(a) / ebob(a, b) * b;
}

int main() {
    struct Cift { int a; int b; };
    for (Cift c : {Cift{12, 18}, Cift{17, 5}, Cift{0, 5}, Cift{100, 75}, Cift{7, 7}}) {
        std::cout << "ebob(" << c.a << ", " << c.b << ") = " << ebob(c.a, c.b)
                  << ",  ekok = " << ekok(c.a, c.b) << "\n";
    }
    return 0;
}
