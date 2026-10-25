// Konu: Üs alma (taban^us)
// Ne gösteriyor: Döngüyle O(n) çarpma ile hızlı üs almayı (O(log n)) ve çarpma sayısı farkını.
// Neden önemli: "Daha hızlı yapabilir misin?" sorusunun güzel bir örneği (böl ve fethet fikri).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 07_us_alma 07_us_alma.cpp

#include <iostream>

// us kez çarpar.
long long usDongu(long long taban, int us, int& carpim) {
    long long sonuc = 1;
    carpim = 0;
    for (int i = 0; i < us; ++i) {
        sonuc *= taban;
        ++carpim;
    }
    return sonuc;
}

// Hızlı üs: us'in ikili yazılışına bakar. Örn. 3^13: 13 = 1101 (ikili) -> 3^8 * 3^4 * 3^1
long long usHizli(long long taban, int us, int& carpim) {
    long long sonuc = 1;
    carpim = 0;
    while (us > 0) {
        if (us & 1) {              // son bit 1 ise bu kuvveti sonuca kat
            sonuc *= taban;
            ++carpim;
        }
        us >>= 1;                  // us'i ikiye böl
        if (us > 0) {
            taban *= taban;        // taban, taban^2, taban^4, taban^8, ...
            ++carpim;
        }
    }
    return sonuc;
}

int main() {
    struct Test { long long taban; int us; };
    for (Test t : {Test{2, 10}, Test{3, 13}, Test{5, 0}, Test{2, 30}, Test{2, 62}}) {
        int c1 = 0;
        int c2 = 0;
        long long a = usDongu(t.taban, t.us, c1);
        long long b = usHizli(t.taban, t.us, c2);
        std::cout << t.taban << "^" << t.us << " = " << a << " (hizli: " << b << ")   carpma sayisi: dongu " << c1 << ", hizli " << c2 << "\n";
    }
    return 0;
}
