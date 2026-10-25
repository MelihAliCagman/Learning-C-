// Konu: Çift mi, tek mi?
// Ne gösteriyor: % işleciyle ve bit işlemiyle çift/tek kontrolünü, negatif sayılarda % tuzağını.
// Neden önemli: En temel mülakat ısınma sorusu; negatif sayıda % davranışı sık yapılan hatadır.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 01_cift_tek 01_cift_tek.cpp

#include <iostream>

bool ciftMi(int n) {
    return n % 2 == 0;
}

// Bit yöntemi: son bit 0 ise sayı çifttir.
bool ciftMiBit(int n) {
    return (n & 1) == 0;
}

int main() {
    int testler[] = {0, 1, 2, 7, -3, -4};
    for (int n : testler) {
        std::cout << n << ": " << (ciftMi(n) ? "cift" : "tek")
                  << "  (bit ile: " << (ciftMiBit(n) ? "cift" : "tek") << ")  n % 2 = " << n % 2 << "\n";
    }
    std::cout << "NOT: -3 % 2 = -1 oldugu icin 'tek mi' diye n % 2 == 1 yazmak YANLIS; n % 2 != 0 yazilir.\n";
    return 0;
}
