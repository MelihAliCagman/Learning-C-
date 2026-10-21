// Konu: const ve pointer: const int* ile int* const farkı
// Ne gösteriyor: Pointer'da iki ayrı şey sabit olabilir: gösterilen değer veya pointer'ın kendisi.
// Neden önemli: Mülakatta çok sorulur; ayrıca const& parametreleri gereksiz kopyayı önler.
// Derleme: g++ -std=c++17 -Wall -Wextra -o const_pointer const_pointer.cpp

#include <iostream>

int main() {
    int a = 10;
    int b = 20;

    // Durum 1: const int* (değer sabit, adres değişebilir)
    const int* p1 = &a;
    // *p1 = 99;
    p1 = &b; 
    
    // Durum 2: int* const (adres sabit, değer değişebilir)
    int* const p2 = &a;
    *p2 = 99;
    // p2 = &b;    

    

    // Her denemeden önce tahmin et: derlenir mi, derlenmez mi?
    std::cout << a << " " << b << "\n";
    return 0;
}
