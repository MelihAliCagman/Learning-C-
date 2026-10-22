// Konu: Veri tipleri, sizeof ve sabit genişlikli tipler
// Ne gösteriyor: Temel tiplerin bellekte kaç bayt tuttuğunu ve int32_t / uint8_t gibi sabit genişlikli tipleri.
// Neden önemli: "int kaç bayttır?" cevabı platforma bağlıdır; haberleşme ve gömülü işlerde boyutu kesin olan tipler gerekir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 04_veri_tipleri 04_veri_tipleri.cpp

#include <cstddef>   // size_t
#include <cstdint>   // int32_t, uint8_t, ...
#include <iostream>

int main() {
    // 1) Temel tiplerin boyutları (bayt).
    // sizeof(tip) derleme zamanında boyutu verir. Örnek:
    std::cout << "sizeof(int)       = " << sizeof(int) << "\n";
    std::cout << "sizeof(char)       = " << sizeof(char) << "\n";
    std::cout << "sizeof(short)      = " << sizeof(short) << "\n";
    std::cout << "sizeof(long)       = " << sizeof(long) << "\n";
    std::cout << "sizeof(long long)  = " << sizeof(long long) << "\n";
    std::cout << "sizeof(float)      = " << sizeof(float) << "\n";
    std::cout << "sizeof(double)     = " << sizeof(double) << "\n";

    // 2) size_t ve pointer
    std::cout << "sizeof(size_t)    = " << sizeof(size_t) << "\n";
    std::cout << "sizeof(int*)       = " << sizeof(int*) << "\n";

    // 3) Sabit genişlikli tipler: boyutu platformdan bağımsız, kesin.
    std::cout << "sizeof(int8_t)    = " << sizeof(int8_t) << "\n";
    std::cout << "sizeof(int16_t)   = " << sizeof(int16_t) << "\n";
    std::cout << "sizeof(int32_t)   = " << sizeof(int32_t) << "\n";
    std::cout << "sizeof(int64_t)   = " << sizeof(int64_t) << "\n";
    std::cout << "sizeof(uint8_t)   = " << sizeof(uint8_t) << "\n";

    // 4) Tuzak: uint8_t aslında bir karakter tipidir. Ekrana nasıl yazılır?
    uint8_t sicaklik = 65;
    std::cout << "sicaklik (dogrudan) = " << sicaklik << "\n";
    std::cout << "sicaklik (sayi olarak) = " << static_cast<int>(sicaklik) << "\n";

    return 0;
}
