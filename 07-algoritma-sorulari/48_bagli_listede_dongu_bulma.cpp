// Konu: Bağlı listede döngü (cycle) bulma: Floyd'un "kaplumbağa ve tavşan" algoritması
// Ne gösteriyor: Biri 1, diğeri 2 adım ilerleyen iki işaretçiyle döngüyü O(1) bellekle tespit etmeyi; döngünün başlangıcını ve uzunluğunu bulmayı.
// Neden önemli: Bağlı liste mülakatlarının en zekice sorusu; "ek bellek kullanmadan nasıl yaparsın?" takibi gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 48_bagli_listede_dongu_bulma 48_bagli_listede_dongu_bulma.cpp

#include <cstddef>
#include <iostream>
#include <vector>

struct Dugum {
    int deger;
    Dugum* sonraki;
};

// Vektörden liste kurar; son düğümü de döner (döngü oluşturmak ve temizlemek için).
Dugum* listeOlustur(const std::vector<int>& v, Dugum*& son) {
    Dugum* bas = nullptr;
    son = nullptr;
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

Dugum* indeksliDugum(Dugum* bas, std::size_t indeks) {
    while (indeks > 0 && bas != nullptr) {
        bas = bas->sonraki;
        --indeks;
    }
    return bas;
}

// Floyd: yavaş 1 adım, hızlı 2 adım ilerler. Döngü varsa hızlı, yavaşı bir noktada yakalar.
// Döngü yoksa hızlı listenin sonuna (nullptr) ulaşır. O(n) zaman, O(1) bellek.
// (Alternatif: gördüğün düğümleri unordered_set'e koy; aynı düğümü tekrar görürsen döngü var. O(n) bellek ister.)
const Dugum* bulusmaNoktasi(const Dugum* bas) {
    const Dugum* yavas = bas;
    const Dugum* hizli = bas;
    while (hizli != nullptr && hizli->sonraki != nullptr) {
        yavas = yavas->sonraki;
        hizli = hizli->sonraki->sonraki;
        if (yavas == hizli) {
            return yavas;
        }
    }
    return nullptr;                              // döngü yok
}

// Döngünün BAŞLANGIÇ düğümü: bir işaretçiyi listenin başına al, ikisini de 1'er adım ilerlet; buluştukları yer döngü başıdır.
// (Matematik: baştan döngü başına uzaklık = buluşma noktasından döngü başına uzaklık (mod döngü uzunluğu).)
const Dugum* donguBasi(const Dugum* bas) {
    const Dugum* bulusma = bulusmaNoktasi(bas);
    if (bulusma == nullptr) {
        return nullptr;
    }
    const Dugum* a = bas;
    const Dugum* b = bulusma;
    while (a != b) {
        a = a->sonraki;
        b = b->sonraki;
    }
    return a;
}

// Döngünün uzunluğu: buluşma noktasından başlayıp tekrar oraya dönene kadar say.
int donguUzunlugu(const Dugum* bas) {
    const Dugum* bulusma = bulusmaNoktasi(bas);
    if (bulusma == nullptr) {
        return 0;
    }
    int uzunluk = 1;
    for (const Dugum* d = bulusma->sonraki; d != bulusma; d = d->sonraki) {
        ++uzunluk;
    }
    return uzunluk;
}

// Döngü varsa temizlemeden önce kırılmalı, yoksa delete sonsuza kadar döner.
void temizle(Dugum* bas, Dugum* son) {
    if (son != nullptr) {
        son->sonraki = nullptr;                  // döngüyü kır
    }
    while (bas != nullptr) {
        Dugum* sonraki = bas->sonraki;
        delete bas;
        bas = sonraki;
    }
}

int main() {
    struct Test { std::vector<int> v; int donguIndeksi; };   // donguIndeksi: son düğüm hangi indekse bağlansın (-1: döngü yok)
    for (Test t : {Test{{1, 2, 3, 4, 5}, -1}, Test{{1, 2, 3, 4, 5}, 2}, Test{{1, 2, 3, 4, 5}, 0}, Test{{7}, 0}, Test{{7}, -1}, Test{{}, -1}}) {
        Dugum* son = nullptr;
        Dugum* bas = listeOlustur(t.v, son);
        if (t.donguIndeksi >= 0) {
            son->sonraki = indeksliDugum(bas, static_cast<std::size_t>(t.donguIndeksi));   // döngü oluştur
        }
        std::cout << "liste " << t.v.size() << " eleman, son -> indeks " << t.donguIndeksi << ": ";
        const Dugum* baslangic = donguBasi(bas);
        if (baslangic == nullptr) {
            std::cout << "dongu YOK\n";
        } else {
            std::cout << "dongu VAR, baslangic degeri = " << baslangic->deger << ", dongu uzunlugu = " << donguUzunlugu(bas) << "\n";
        }
        temizle(bas, son);
    }
    return 0;
}
