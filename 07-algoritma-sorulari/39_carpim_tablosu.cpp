// Konu: Çarpım tablosu
// Ne gösteriyor: Tek sayının tablosunu ve iç içe döngüyle 5x5 ızgarayı; std::setw ile hizalamayı.
// Neden önemli: İç içe döngü ve biçimli çıktı alıştırması; deseni matematiksel olarak düşünmeyi ölçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 39_carpim_tablosu 39_carpim_tablosu.cpp

#include <iomanip>
#include <iostream>

int main() {
    int n = 7;
    std::cout << n << " lu carpim tablosu:\n";
    for (int i = 1; i <= 10; ++i) {
        std::cout << n << " x " << i << " = " << n * i << "\n";
    }

    std::cout << "\n5x5 tablo:\n";
    for (int satir = 1; satir <= 5; ++satir) {
        for (int sutun = 1; sutun <= 5; ++sutun) {
            std::cout << std::setw(4) << satir * sutun;      // her sayıya 4 karakterlik yer ayır
        }
        std::cout << "\n";
    }
    return 0;
}
