// Konu: Değer değiştirme (swap): referans ve pointer ile
// Ne gösteriyor: Aynı işi yapan iki fonksiyon; biri referans, diğeri pointer alıyor.
// Neden önemli: "Değerle geçirme" kopya üretir; orijinali değiştirmek için referans veya pointer gerekir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o swap swap.cpp

#include <iostream>

// Referansla: a ve b, çağıran taraftaki değişkenlerin takma adıdır.
void swapRef(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Pointer ile: a ve b adres tutar; değere ulaşmak için * kullanılır.
void swapPtr(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 3;
    int y = 7;

    std::cout << "Basta:        x=" << x << " y=" << y << "\n";

    swapRef(x,y);
    std::cout << "swapRef sonra: x=" << x << " y=" << y << "\n";

    swapPtr(&x,&y);
    std::cout << "swapPtr sonra: x=" << x << " y=" << y << "\n";

    return 0;
}
