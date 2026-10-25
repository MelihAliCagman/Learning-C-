// Konu: Stack ve heap: otomatik ve elle yönetilen bellek
// Ne gösteriyor: Yerel (stack) değişken ile new ile oluşturulan (heap) nesnenin ömür ve adres farkını.
// Neden önemli: "Stack ile heap farkı nedir?" mülakatın en sık sorulan bellek sorusu; bellek sızıntısının temeli.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 08_stack_heap 08_stack_heap.cpp

#include <iostream>

// new ile heap'te bir int oluşturur ve adresini döner.
// Dikkat: sahipliği çağırana devreder; çağıran delete etmek zorundadır.
int* heapOlustur(int deger) {
    return new int(deger);
}

int main() {
    // 1) Stack: yerel değişken. Blok bitince otomatik yok olur.
    int x = 10;

    // 2) Heap: new ile oluşturulur, delete edilene kadar yaşar.
    int* p = new int(20);   // p kendisi stack'te, gösterdiği int heap'te!

    std::cout << "x  = " << x << "   adresi: " << &x << "\n";
    std::cout << "*p = " << *p << "   adresi: " << p << "\n";
    std::cout << "p  = " << p << "   adresi: " << &p << "\n";
    // 3) Heap'i geri ver: new ile alınan, delete ile iade edilir.
    delete p;
    p = nullptr;

    // 4) Fonksiyondan heap nesnesi alma.
    int* q = heapOlustur(30);
    std::cout << "*q = " << *q << "\n";
    delete q;
    q = nullptr;

    return 0;
}
