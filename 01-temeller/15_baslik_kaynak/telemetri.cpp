// telemetri.cpp: TANIMLAR (definition) burada durur.
#include "telemetri.h"

namespace telemetri {

// extern bildirimin TANIMI: programın tamamında yalnızca BİR .cpp'de olmalı.
int toplamOlcum = 0;

// İsimsiz namespace: bu fonksiyon yalnızca bu .cpp dosyasında görünür (iç bağlantı, "dosya düzeyinde static" yerine).
namespace {
double yuvarla1(double x) {
    return static_cast<long long>(x * 10 + (x >= 0 ? 0.5 : -0.5)) / 10.0;
}
}  // namespace

double ortalama(const Olcum* olcumler, std::size_t n) {
    if (n == 0) {
        return 0.0;
    }
    double toplam = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        toplam += olcumler[i].deger;
    }
    toplamOlcum += static_cast<int>(n);
    return toplam / static_cast<double>(n);
}

std::string metin(const Olcum& o) {
    return "olcum#" + std::to_string(o.id) + " = " + std::to_string(yuvarla1(o.deger));
}

}  // namespace telemetri
