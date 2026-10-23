// Konu: Tanımsız davranış (undefined behavior, UB) örnekleri
// Ne gösteriyor: Sık görülen UB türlerini, hangilerini derleyicinin uyardığını ve optimizasyon düzeyinin sonucu nasıl değiştirdiğini.
// Neden önemli: UB "hata verir" demek değildir: program çökebilir, yanlış çalışabilir ya da doğru görünebilir; mülakatta "UB nedir, örnek ver?" sık sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 16_tanimsiz_davranis 16_tanimsiz_davranis.cpp
// NOT: Bu dosya BİLEREK uyarı üretir (aşağıda "UYARI VERİR" yazan fonksiyonlar). Her UB senaryosu ayrı çalıştırılır:
//      .\16_tanimsiz_davranis 1   (1'den 11'e kadar), argümansız çalıştırınca güvenli demolar ve senaryo listesi gelir.
// Karşılaştırma: g++ -O2 ... ile de derle; bazı senaryoların sonucu değişir.

#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ---------------------------------------------------------------- 1) İşaretli taşma
// Derleyici "işaretli taşma olmaz" varsayar: x + 1 > x her zaman doğru kabul edilebilir.
bool birFazlasiBuyukMu(int x) {
    return x + 1 > x;
}

// ---------------------------------------------------------------- 8) Yerel değişkene referans döndürmek
// UYARI VERİR (-Wreturn-local-addr): fonksiyon bitince yerel değişken yok olur.
const int& yerelReferans() {
    int yerel = 42;
    return yerel;
}

// ---------------------------------------------------------------- 9) Dönüş değeri olmayan yol
// UYARI VERİR (-Wreturn-type): x <= 0 için return yok.
int bazenDonmeyen(int x) {
    if (x > 0) {
        return 1;
    }
}

void senaryo(int no, int argc) {
    switch (no) {
        case 1: {   // İşaretli taşma
            std::cout << "INT_MAX + 1 > INT_MAX ? " << birFazlasiBuyukMu(INT_MAX) << "\n";
            break;
        }
        case 2: {   // Başlatılmamış değişken
            int u;   // değer verilmedi
            std::cout << "baslatilmamis u = " << u << "\n";
            break;
        }
        case 3: {   // Dizi sınırı aşma (okuma)
            int a[3] = {1, 2, 3};
            int indeks = 3 + argc + 1;   // 5 gibi: sınır dışı
            std::cout << "a[" << indeks << "] = " << a[indeks] << "  (cop deger)\n";
            break;
        }
        case 4: {   // Null pointer'a erişim
            int* p = nullptr;
            std::cout << "null pointer okunuyor...\n";
            std::cout << *p << "\n";
            break;
        }
        case 5: {   // Tamsayı sıfıra bölme
            int sifir = argc - 2;   // argc = 2 iken 0
            std::cout << "10 / 0 hesaplaniyor...\n";
            std::cout << 10 / sifir << "\n";
            break;
        }
        case 6: {   // delete sonrası kullanma (use-after-free)
            int* p = new int(5);
            delete p;
            std::cout << "delete sonrasi *p = " << *p << "  (cokmeyebilir ama gecersiz)\n";
            break;
        }
        case 7: {   // Çift delete (double free)
            int* p = new int(5);
            delete p;
            std::cout << "ikinci delete...\n";
            delete p;
            std::cout << "ikinci delete bitti\n";
            break;
        }
        case 8: {   // Yerel değişkene referans
            const int& r = yerelReferans();
            std::cout << "dangling referans = " << r << "\n";
            break;
        }
        case 9: {   // Dönüş değeri olmayan yol
            std::cout << "bazenDonmeyen(-1) = " << bazenDonmeyen(-1) << "\n";
            break;
        }
        case 10: {  // Kaydırma miktarı genişliği aşıyor
            int kaydirma = 30 + argc * 5;   // 40: int 32 bit
            std::cout << "1 << " << kaydirma << " = " << (1 << kaydirma) << "\n";
            break;
        }
        case 11: {  // String sabitini değiştirmek
            char* p = const_cast<char*>("merhaba");
            std::cout << "string sabiti degistiriliyor...\n";
            p[0] = 'M';
            std::cout << p << "\n";
            break;
        }
        default:
            std::cout << "gecersiz senaryo\n";
    }
}

void guvenliDemolar() {
    std::cout << "=== GUVENLI (tanimli) davranislar ===\n";

    // İşaretsiz taşma TANIMLIDIR: başa sarar.
    unsigned int u = UINT_MAX;
    std::cout << "UINT_MAX + 1 = " << (u + 1) << "  (tanimli: basa sarar)\n";

    // İşaretli taşmayı ÖNCEDEN kontrol et.
    int a = INT_MAX;
    int b = 1;
    if (a > INT_MAX - b) {
        std::cout << "INT_MAX + 1 tasar: toplama yapilmadi (onceden kontrol)\n";
    }

    // Başlatılmış değişken ve süslü parantez ile sıfır değeri.
    int s{};
    std::cout << "int s{} = " << s << "\n";

    // Sınır kontrollü erişim.
    std::vector<int> v = {1, 2, 3};
    try {
        std::cout << v.at(10) << "\n";
    } catch (const std::out_of_range&) {
        std::cout << "v.at(10) -> out_of_range istisnasi (v[10] tanimsiz davranis olurdu)\n";
    }

    // Null kontrolü.
    int* p = nullptr;
    if (p != nullptr) {
        std::cout << *p << "\n";
    } else {
        std::cout << "p null: erisilmedi\n";
    }

    // Sıfıra bölmeden önce kontrol.
    int bolen = 0;
    if (bolen != 0) {
        std::cout << 10 / bolen << "\n";
    } else {
        std::cout << "bolen 0: bolme yapilmadi\n";
    }

    std::cout << "\nSenaryolar (her biri AYRI calistirilir):\n"
                 "  1 isaretli tasma   2 baslatilmamis   3 dizi siniri    4 null pointer\n"
                 "  5 sifira bolme     6 delete sonrasi  7 cift delete    8 yerel referans\n"
                 "  9 return yok       10 kaydirma       11 string sabiti\n"
                 "ornek: .\\16_tanimsiz_davranis 4\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        guvenliDemolar();
        return 0;
    }
    senaryo(std::atoi(argv[1]), argc);
    return 0;
}
