// telemetri.h: BİLDİRİMLER (declaration) burada durur; gövdeler telemetri.cpp'dedir.
// Include guard: bu başlık aynı .cpp içinde iki kez gelirse ikinci seferde içeriği atlanır.
#ifndef TELEMETRI_H
#define TELEMETRI_H

#include <cstddef>
#include <string>

namespace telemetri {

struct Olcum {
    int id;
    double deger;
};

constexpr int MAKS_OLCUM = 8;   // constexpr sabit: başlıkta tanımlanması güvenli

// Fonksiyon BİLDİRİMİ: gövde telemetri.cpp'de.
double ortalama(const Olcum* olcumler, std::size_t n);
std::string metin(const Olcum& o);

// extern: "bu değişken VAR ama TANIMI başka bir .cpp'de". (Tanımı burada yapsaydık: multiple definition hatası.)
extern int toplamOlcum;

// Gövdesi başlıkta olan fonksiyon inline olmalıdır (ODR, 12. örnekteki konu).
inline int kare(int x) { return x * x; }

}  // namespace telemetri

#endif  // TELEMETRI_H
