// Konu: Operatörler: ++i / i++, kısa devre, bit düzeyi ve mantıksal operatörler, öncelik
// Ne gösteriyor: Sık karıştırılan operatörlerin gerçek sonuçlarını ve öncelik tuzağını.
// Neden önemli: Mülakatta "i++ ile ++i farkı", "& ile && farkı" ve bit maskeleme soruları çok sık gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 07_operatorler 07_operatorler.cpp

#include <iostream>

// Çağrıldığını ekrana yazan ve true dönen yardımcı fonksiyon.
bool kontrol(const char* ad) {
    std::cout << "  [" << ad << " calisti]\n";
    return true;
}

int main() {
    // 1) Artırma: i++ (sonra artır) ile ++i (önce artır)
    int i = 5;
    int a = i++;   // a ne olur? i ne olur?
    int b = ++i;   // b ne olur? i ne olur?
    std::cout << "i=" << i << " a=" << a << " b=" << b << "\n";

    // 2) Kısa devre (short-circuit): && ve || sağ tarafı her zaman çalıştırmaz.
    std::cout << "2a) false && kontrol:\n";
    bool r1 = false && kontrol("B");
    std::cout << "r1 = " << r1 << "\n";

    std::cout << "2b) true && kontrol:\n";
    bool r2 = true && kontrol("B");
    std::cout << "r2 = " << r2 << "\n";

    std::cout << "2c) true || kontrol:\n";
    bool r3 = true || kontrol("C");
    std::cout << "r3 = " << r3 << "\n";

    // 3) Bit düzeyi (&, |, ^, ~, <<) ile mantıksal (&&, ||) operatör farkı.
    int x = 6;   // ikili: 0110
    int y = 3;   // ikili: 0011
    std::cout << "3) x & y  = " << (x & y) << "\n";
    std::cout << "x | y  = " << (x | y) << "\n";
    std::cout << "x ^ y  = " << (x ^ y) << "\n";
    std::cout << "x && y = " << (x && y) << "\n";
    std::cout << "1 << 4 = " << (1 << 4) << "\n";

    // 4) Öncelik tuzağı: == işareti & işaretinden ÖNCE işlenir.
    int bayraklar = 5;   // ikili: 0101 (bit 1 kapalı)
    bool bit1_kapali = bayraklar & 2 == 0;      // niyet: bit 1 kapalı mı?
    std::cout << "bit1_kapali = " << bit1_kapali << "\n";
    bool bit1_kapali_dogru = (bayraklar & 2) == 0;
    std::cout << "bit1_kapali_dogru = " << bit1_kapali_dogru << "\n";
    return 0;
}
