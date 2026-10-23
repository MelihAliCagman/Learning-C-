// Konu: Bit işlemleri: set, clear, toggle, kontrol, maske ve alan çıkarma
// Ne gösteriyor: Tek bir baytın bitlerini açma/kapama/tersleme/okuma kalıplarını, bayrak baytını ve bit sayma klasiğini.
// Neden önemli: Gömülü sistem, haberleşme protokolü (MAVLink dahil) ve durum register'ları bit düzeyinde çalışır; mülakatta çok sorulur.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 10_bit_islemleri 10_bit_islemleri.cpp

#include <bitset>
#include <cstdint>
#include <iostream>

// Bir baytı ikili ve onluk olarak yazdırır. std::bitset<8> 8 biti '0'/'1' olarak gösterir.
void yaz(const char* etiket, uint8_t v) {
    std::cout << etiket << std::bitset<8>(v) << "  (" << static_cast<int>(v) << ")\n";
}

// n. biti (sağdan, 0'dan başlayarak) kontrol eder: açıksa true.
bool bitAcikMi(uint8_t v, int n) {
    return (v & (1u << n)) != 0;
}

// n. biti 1 yapar (set).
uint8_t bitAc(uint8_t v, int n) {
    return static_cast<uint8_t>(v | (1u << n));
}

// n. biti 0 yapar (clear).
uint8_t bitKapat(uint8_t v, int n) {
    return static_cast<uint8_t>(v & ~(1u << n));
}

// n. biti tersler (toggle): 0 ise 1, 1 ise 0.
uint8_t bitTersle(uint8_t v, int n) {
    return static_cast<uint8_t>(v ^ (1u << n));
}

// Kaç bit açık? (Kernighan yöntemi: v & (v-1) en sağdaki 1 bitini siler.)
int bitSay(uint8_t v) {
    int sayac = 0;
    while (v != 0) {
        v = static_cast<uint8_t>(v & (v - 1));
        ++sayac;
    }
    return sayac;
}

// 2'nin kuvveti mi? 2'nin kuvvetlerinde tek bir bit açıktır: 8 = 1000, 7 = 0111, 8 & 7 = 0.
bool ikininKuvvetiMi(unsigned x) {
    return x != 0 && (x & (x - 1)) == 0;
}

// Bir durum baytındaki bayrakların bit numaraları (her biri tek bir bitlik maske).
constexpr uint8_t BAYRAK_SILAHLI  = 1 << 0;   // 0000 0001
constexpr uint8_t BAYRAK_GPS_VAR  = 1 << 1;   // 0000 0010
constexpr uint8_t BAYRAK_DUSUK_PIL = 1 << 2;  // 0000 0100

int main() {
    // 1) Temel operatörler: &, |, ^, ~, <<, >>
    uint8_t a = 0b00101100;   // 44
    uint8_t b = 0b00001111;   // 15
    std::cout << "--- 1) Temel operatorler ---\n";
    yaz("a          = ", a);
    yaz("b          = ", b);
    yaz("a & b      = ", a & b);
    yaz("a | b      = ", a | b);
    yaz("a ^ b      = ", a ^ b);
    yaz("~a         = ", static_cast<uint8_t>(~a));
    yaz("a << 1     = ", static_cast<uint8_t>(a << 1));
    yaz("a >> 2     = ", a >> 2);

    // 2) Tek bit: set, clear, toggle, kontrol
    std::cout << "\n--- 2) Set / clear / toggle / kontrol ---\n";
    uint8_t v = 0b00000000;
    yaz("basta            = ", v);
    v = bitAc(v, 3);
    yaz("bit 3 acildi     = ", v);
    v = bitAc(v, 6);
    yaz("bit 6 acildi     = ", v);
    v = bitKapat(v, 3);
    yaz("bit 3 kapatildi  = ", v);
    v = bitTersle(v, 0);
    yaz("bit 0 terslendi  = ", v);
    v = bitTersle(v, 0);
    yaz("bit 0 tekrar ters= ", v);
    std::cout << "bit 6 acik mi? " << bitAcikMi(v, 6) << "\n";
    std::cout << "bit 3 acik mi? " << bitAcikMi(v, 3) << "\n";

    // 3) Bayrak baytı (durum register'ı gibi)
    std::cout << "\n--- 3) Bayrak bayti ---\n";
    uint8_t durum = 0;
    durum |= BAYRAK_GPS_VAR;       // GPS var bayrağını aç
    durum |= BAYRAK_SILAHLI;       // silahlı bayrağını aç
    yaz("durum                 = ", durum);
    std::cout << "silahli mi?   " << ((durum & BAYRAK_SILAHLI) != 0) << "\n";
    std::cout << "dusuk pil mi? " << ((durum & BAYRAK_DUSUK_PIL) != 0) << "\n";
    durum &= static_cast<uint8_t>(~BAYRAK_SILAHLI);   // silahli bayrağını kapat
    yaz("silahli kapatildi     = ", durum);

    // 4) Alan çıkarma: bir baytı iki 4 bitlik yarıya (nibble) bölmek
    std::cout << "\n--- 4) Alan cikarma ---\n";
    uint8_t paket = 0xA5;                 // 1010 0101
    int yuksek = (paket >> 4) & 0x0F;     // üst 4 bit: 1010 = 10
    int dusuk  = paket & 0x0F;            // alt 4 bit:  0101 = 5
    yaz("paket = ", paket);
    std::cout << "ust 4 bit = " << yuksek << ", alt 4 bit = " << dusuk << "\n";

    // 5) Klasik mülakat soruları
    std::cout << "\n--- 5) Klasikler ---\n";
    std::cout << "bitSay(0b10110111)   = " << bitSay(0b10110111) << "\n";
    std::cout << "bitSay(0)            = " << bitSay(0) << "\n";
    std::cout << "ikininKuvvetiMi(8)   = " << ikininKuvvetiMi(8) << "\n";
    std::cout << "ikininKuvvetiMi(6)   = " << ikininKuvvetiMi(6) << "\n";
    std::cout << "ikininKuvvetiMi(0)   = " << ikininKuvvetiMi(0) << "\n";

    // 6) Sola kaydırma çarpma, sağa kaydırma bölme demektir (işaretsiz sayılarda)
    std::cout << "\n--- 6) Kaydirma = carpma/bolme ---\n";
    unsigned sayi = 5;
    std::cout << "5 << 1 = " << (sayi << 1) << "  (5 * 2)\n";
    std::cout << "5 << 3 = " << (sayi << 3) << "  (5 * 8)\n";
    std::cout << "40 >> 2 = " << (40u >> 2) << "  (40 / 4)\n";

    return 0;
}
