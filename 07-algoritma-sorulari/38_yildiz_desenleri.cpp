// Konu: Yıldız desenleri (iç içe döngüler)
// Ne gösteriyor: Dış döngünün satırı, iç döngünün sütunu kontrol ettiği kalıbı: üçgen, ters üçgen ve piramit.
// Neden önemli: İç içe döngü mantığını ölçen en yaygın başlangıç sorusu.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 38_yildiz_desenleri 38_yildiz_desenleri.cpp

#include <iostream>

// Satır i'de i tane yıldız.
void ucgen(int yukseklik) {
    for (int satir = 1; satir <= yukseklik; ++satir) {
        for (int sutun = 1; sutun <= satir; ++sutun) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

// Satır i'de (yukseklik - i + 1) yıldız.
void tersUcgen(int yukseklik) {
    for (int satir = yukseklik; satir >= 1; --satir) {
        for (int sutun = 1; sutun <= satir; ++sutun) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

// Satır i'de önce (yukseklik - i) boşluk, sonra (2*i - 1) yıldız.
void piramit(int yukseklik) {
    for (int satir = 1; satir <= yukseklik; ++satir) {
        for (int bosluk = 1; bosluk <= yukseklik - satir; ++bosluk) {
            std::cout << " ";
        }
        for (int yildiz = 1; yildiz <= 2 * satir - 1; ++yildiz) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

int main() {
    std::cout << "Ucgen (5):\n";
    ucgen(5);
    std::cout << "\nTers ucgen (4):\n";
    tersUcgen(4);
    std::cout << "\nPiramit (5):\n";
    piramit(5);
    return 0;
}
