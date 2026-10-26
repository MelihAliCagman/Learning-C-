// Konu: Tek yönlü bağlı listeyi (singly linked list) ters çevirmek
// Ne gösteriyor: Üç işaretçiyle (önceki, şimdiki, sonraki) döngülü çözümü ve özyineli çözümü; boş/tek elemanlı liste kenar durumlarını.
// Neden önemli: Mülakatın en meşhur bağlı liste sorusu; işaretçi (pointer) mantığını ve bellek yönetimini aynı anda ölçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 41_bagli_liste_ters_cevir 41_bagli_liste_ters_cevir.cpp

#include <iostream>
#include <vector>

struct Dugum {
    int deger;
    Dugum* sonraki;
};

// Vektörden liste kurar: bas -> 1 -> 2 -> 3 -> nullptr
Dugum* listeOlustur(const std::vector<int>& v) {
    Dugum* bas = nullptr;
    Dugum* son = nullptr;
    for (int x : v) {
        Dugum* yeni = new Dugum{x, nullptr};
        if (bas == nullptr) {
            bas = yeni;
        } else {
            son->sonraki = yeni;
        }
        son = yeni;
    }
    return bas;
}

void yaz(const char* etiket, const Dugum* bas) {
    std::cout << etiket;
    for (const Dugum* d = bas; d != nullptr; d = d->sonraki) {
        std::cout << d->deger << " -> ";
    }
    std::cout << "nullptr\n";
}

// Belleği geri verir (new ile alınan her düğüm delete edilmeli).
void temizle(Dugum* bas) {
    while (bas != nullptr) {
        Dugum* sonraki = bas->sonraki;
        delete bas;
        bas = sonraki;
    }
}

// Döngülü: her düğümün "sonraki" bağlantısını geriye çevirir. O(n) zaman, O(1) bellek.
//   önceki  şimdiki  sonraki
//   null     1  ->    2 -> 3        adım 1: 1'in sonraki'sini null yap -> null <- 1   2 -> 3
Dugum* tersCevir(Dugum* bas) {
    Dugum* onceki = nullptr;
    Dugum* simdiki = bas;
    while (simdiki != nullptr) {
        Dugum* sonraki = simdiki->sonraki;   // 1) bağlantıyı koparmadan önce sakla
        simdiki->sonraki = onceki;           // 2) bağlantıyı geriye çevir
        onceki = simdiki;                    // 3) bir adım ilerle
        simdiki = sonraki;
    }
    return onceki;                           // yeni baş: eski son düğüm
}

// Özyineli: önce kalanı ters çevir, sonra kendini sona bağla. O(n) zaman, O(n) stack.
Dugum* tersCevirOzyineli(Dugum* bas) {
    if (bas == nullptr || bas->sonraki == nullptr) {   // taban durum: boş ya da tek düğüm
        return bas;
    }
    Dugum* yeniBas = tersCevirOzyineli(bas->sonraki);
    bas->sonraki->sonraki = bas;                       // arkadaki düğüm artık bana işaret etsin
    bas->sonraki = nullptr;                            // ben artık son düğümüm
    return yeniBas;
}

int main() {
    std::vector<std::vector<int>> testler = {{1, 2, 3, 4, 5}, {1, 2}, {7}, {}};
    for (const auto& v : testler) {
        Dugum* liste = listeOlustur(v);
        yaz("once          : ", liste);
        liste = tersCevir(liste);
        yaz("tersCevir     : ", liste);
        liste = tersCevirOzyineli(liste);
        yaz("ozyineli(geri): ", liste);   // tekrar ters çevirince orijinal sıra
        temizle(liste);
        std::cout << "\n";
    }
    return 0;
}
