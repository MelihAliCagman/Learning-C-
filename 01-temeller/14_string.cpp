// Konu: C tarzı string (char dizisi) ve std::string
// Ne gösteriyor: Sonlandırıcı '\0', strlen/sizeof farkı, == tuzağı, sınırlı kopyalama ve std::string'in güvenli kullanımı.
// Neden önemli: C stringleri buffer overflow'un ana kaynağıdır; "std::string neden daha güvenli?" ve string ters çevirme/palindrom mülakat klasiğidir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 14_string 14_string.cpp

#include <algorithm>   // std::reverse
#include <cstdio>      // snprintf
#include <cstring>     // strlen, strcmp, strncpy
#include <iostream>
#include <stdexcept>
#include <string>

// Palindrom mu? (iki pointer yaklaşımı: baştan ve sondan karşılaştır)
bool palindromMu(const std::string& s) {
    if (s.empty()) {
        return true;
    }
    std::size_t sol = 0;
    std::size_t sag = s.size() - 1;
    while (sol < sag) {
        if (s[sol] != s[sag]) {
            return false;
        }
        ++sol;
        --sag;
    }
    return true;
}

// Elle ters çevirme (std::reverse'ün yaptığı iş)
std::string tersCevir(std::string s) {   // değerle: kopya üzerinde çalışıyoruz, orijinal bozulmaz
    if (s.size() < 2) {
        return s;
    }
    std::size_t sol = 0;
    std::size_t sag = s.size() - 1;
    while (sol < sag) {
        std::swap(s[sol], s[sag]);
        ++sol;
        --sag;
    }
    return s;
}

int main() {
    // ------------------------------------------------------------ 1) C stringi = '\0' ile biten char dizisi
    std::cout << "--- 1) C stringi ---\n";
    char a[] = "abc";                 // 'a','b','c','\0' -> 4 bayt
    std::cout << "sizeof(a) = " << sizeof(a) << ", strlen(a) = " << std::strlen(a) << "  (sizeof sonlandiriciyi sayar, strlen saymaz)\n";
    char elle[4] = {'o', 'k', '!', '\0'};
    std::cout << "elle olusturulan: " << elle << "\n";
    // char kotu[3] = {'a', 'b', 'c'};   // '\0' YOK: std::cout << kotu; dizinin ötesini okur (tanımsız davranış)

    // char dizisi değiştirilebilir, string sabiti (literal) DEĞİŞTİRİLEMEZ
    a[0] = 'X';
    std::cout << "char dizisi degistirildi: " << a << "\n";
    const char* sabit = "merhaba";   // literal: salt okunur bellekte; const olmalı
    // sabit[0] = 'M';               // tanımsız davranış (genelde çökme)
    std::cout << "sabit + 3 = " << (sabit + 3) << "  (pointer aritmetigi: 4. karakterden itibaren)\n";

    // ------------------------------------------------------------ 2) == tuzağı: adresleri karşılaştırır!
    std::cout << "\n--- 2) == ve strcmp ---\n";
    char s1[] = "kedi";
    char s2[] = "kedi";
    const char* p1 = s1;
    const char* p2 = s2;
    std::cout << "p1 == p2 (adres karsilastirir) = " << (p1 == p2) << "\n";
    std::cout << "strcmp(p1, p2) == 0 (icerik)    = " << (std::strcmp(p1, p2) == 0) << "\n";
    std::cout << "strcmp(\"abc\", \"abd\") < 0 mi?   = " << (std::strcmp("abc", "abd") < 0) << "\n";

    // ------------------------------------------------------------ 3) Sınırlı kopyalama
    std::cout << "\n--- 3) Sinirli kopyalama (buffer overflow'dan korunma) ---\n";
    char kucuk[6];
    // std::strcpy(kucuk, "merhaba dunya");   // BUFFER OVERFLOW: 14 bayt 6 baytlık yere sığmaz (tanımsız davranış)
    int istenen = std::snprintf(kucuk, sizeof(kucuk), "%s", "merhaba dunya");
    std::cout << "snprintf sonucu kucuk = \"" << kucuk << "\" (kesildi), sigsaydi uzunluk = " << istenen << "\n";

    char hedef[8];
    std::strncpy(hedef, "abcdefghij", sizeof(hedef) - 1);
    hedef[sizeof(hedef) - 1] = '\0';   // strncpy sonlandırıcıyı GARANTİ ETMEZ, elle koy
    std::cout << "strncpy + elle '\\0' = \"" << hedef << "\"\n";

    // ------------------------------------------------------------ 4) std::string
    std::cout << "\n--- 4) std::string ---\n";
    std::string s = "merhaba";
    s += " dunya";                                   // otomatik büyür
    std::string t = s + "!";                         // birleştirme
    std::cout << t << "  (size = " << t.size() << ")\n";
    std::cout << "s == \"merhaba dunya\" ? " << (s == "merhaba dunya") << "  (icerik karsilastirir)\n";
    std::cout << "substr(0, 7) = " << s.substr(0, 7) << ", find(\"dunya\") = " << s.find("dunya") << "\n";
    std::cout << "find(\"xyz\") == npos ? " << (s.find("xyz") == std::string::npos) << "\n";

    std::string kopya = s;      // derin kopya: kopya değişince orijinal etkilenmez
    kopya[0] = 'M';
    std::cout << "kopya = " << kopya << ", orijinal = " << s << "\n";

    s.replace(0, 7, "selam");
    s.insert(0, ">> ");
    s.erase(s.size() - 1);      // son karakteri sil
    std::cout << "replace/insert/erase sonrasi: " << s << "\n";

    const char* cstr = s.c_str();   // C API'leri için '\0' ile biten görünüm
    std::cout << "c_str() uzunluk = " << std::strlen(cstr) << "\n";

    // ------------------------------------------------------------ 5) Güvenli erişim ve dönüşüm
    std::cout << "\n--- 5) at(), stoi, to_string ---\n";
    std::string kisa = "abc";
    try {
        char c = kisa.at(10);        // [] sınır kontrolü yapmaz, at() yapar
        std::cout << c << "\n";
    } catch (const std::out_of_range&) {
        std::cout << "at(10) -> out_of_range yakalandi\n";
    }
    std::cout << "stoi(\"42\") + 1 = " << std::stoi("42") + 1 << "\n";
    try {
        int x = std::stoi("abc");
        std::cout << x << "\n";
    } catch (const std::invalid_argument&) {
        std::cout << "stoi(\"abc\") -> invalid_argument yakalandi\n";
    }
    std::cout << "to_string(3.5) = " << std::to_string(3.5) << ", to_string(7) = " << std::to_string(7) << "\n";

    // ------------------------------------------------------------ 6) SSO ve boyut (derleyiciye bağlı)
    std::cout << "\n--- 6) std::string'in ic yapisi (bu derleyicide) ---\n";
    std::string bos;
    std::cout << "sizeof(std::string) = " << sizeof(bos) << ", bos string capacity = " << bos.capacity() << " (kisa stringler nesnenin icinde, heap'e gerek yok: SSO)\n";

    // ------------------------------------------------------------ 7) Klasik mülakat soruları
    std::cout << "\n--- 7) Ters cevirme ve palindrom ---\n";
    std::string kelime = "radar";
    std::cout << "tersCevir(\"merhaba\") = " << tersCevir("merhaba") << "\n";
    std::string r = "merhaba";
    std::reverse(r.begin(), r.end());
    std::cout << "std::reverse         = " << r << "\n";
    std::cout << kelime << " palindrom mu? " << palindromMu(kelime) << "\n";
    std::cout << "merhaba palindrom mu? " << palindromMu("merhaba") << "\n";
    std::cout << "bos string palindrom mu? " << palindromMu("") << "\n";

    return 0;
}
