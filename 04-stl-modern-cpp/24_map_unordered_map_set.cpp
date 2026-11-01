// Konu: std::map, std::unordered_map ve std::set: sıralı ve hash tabanlı konteynerler
// Ne gösteriyor: map'in sıralı (kırmızı-siyah ağaç), unordered_map'in sırasız (hash tablosu) olmasını; operator[] tuzağını; find/insert/at farkını; set'in tekrarsızlığını; hız karşılaştırmasını.
// Neden önemli: "map ile unordered_map farkı, karmaşıklıkları, operator[] neden tehlikeli?" STL mülakatının ikinci en sık sorusudur.
// Derleme: g++ -std=c++17 -Wall -Wextra -O2 -o 24_map_unordered_map_set 24_map_unordered_map_set.cpp

#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {
    // ------------------------------------------------------------ 1) map: anahtara göre SIRALI
    std::cout << "--- 1) map: siralidir (anahtara gore) ---\n";
    std::map<std::string, int> yas;
    yas["zeynep"] = 31;
    yas["ali"] = 25;
    yas["mehmet"] = 40;
    yas.insert({"ayse", 22});
    for (const auto& [ad, deger] : yas) {           // yapılandırılmış bağlama (C++17)
        std::cout << "  " << ad << " = " << deger << "\n";
    }
    std::cout << "  ilk (en kucuk anahtar): " << yas.begin()->first << ", son: " << yas.rbegin()->first << "\n";

    // ------------------------------------------------------------ 2) operator[] tuzağı
    std::cout << "\n--- 2) operator[] yoksa EKLER ---\n";
    std::cout << "  size (once) = " << yas.size() << "\n";
    int aranan = yas["yok"];                         // "yok" anahtarı yoktu: varsayılan değerle (0) OLUŞTURULDU
    std::cout << "  yas[\"yok\"] okundu -> " << aranan << ", size (sonra) = " << yas.size() << "  (okumak bile ekledi!)\n";
    std::cout << "  find ile guvenli arama: ";
    auto it = yas.find("bulunmayan");
    std::cout << (it == yas.end() ? "bulunamadi (eklemedi)" : "bulundu") << ", size = " << yas.size() << "\n";
    try {
        std::cout << yas.at("baska");
    } catch (const std::out_of_range&) {
        std::cout << "  at(\"baska\") -> out_of_range istisnasi (eklemez)\n";
    }

    // ------------------------------------------------------------ 3) insert, emplace, try_emplace
    std::cout << "\n--- 3) insert var olan anahtari DEGISTIRMEZ ---\n";
    auto sonuc = yas.insert({"ali", 99});            // pair<iterator, bool>: bool eklendi mi?
    std::cout << "  insert({\"ali\", 99}) eklendi mi? " << sonuc.second << ", ali hala = " << yas["ali"] << "\n";
    yas["ali"] = 26;                                 // [] ile atama var olanı güncelleler
    std::cout << "  yas[\"ali\"] = 26 sonrasi ali = " << yas["ali"] << "\n";

    // ------------------------------------------------------------ 4) unordered_map
    std::cout << "\n--- 4) unordered_map: sirasiz (hash tablosu) ---\n";
    std::unordered_map<std::string, int> hash;
    hash["ali"] = 25;
    hash["ayse"] = 22;
    hash["mehmet"] = 40;
    std::cout << "  hash[\"ayse\"] = " << hash["ayse"] << ", size = " << hash.size() << ", bucket sayisi = " << hash.bucket_count() << "\n";
    std::cout << "  gezme sirasi BELIRSIZDIR (bu makinede): ";
    for (const auto& cift : hash) {
        std::cout << cift.first << " ";
    }
    std::cout << "\n";

    // ------------------------------------------------------------ 5) set ve unordered_set
    std::cout << "\n--- 5) set: tekrarsiz ve sirali ---\n";
    std::set<int> kume = {5, 1, 3, 3, 1, 9};
    std::cout << "  {5,1,3,3,1,9} -> ";
    for (int x : kume) {
        std::cout << x << " ";
    }
    std::cout << "(size = " << kume.size() << ")\n";
    std::cout << "  insert(3) eklendi mi? " << kume.insert(3).second << ", insert(4) eklendi mi? " << kume.insert(4).second << "\n";
    auto alt = kume.lower_bound(4);                  // 4'e eşit veya büyük ilk eleman (sıralı olduğu için mümkün)
    std::cout << "  lower_bound(4) = " << *alt << "  (unordered_set'te yok: sirasiz)\n";
    std::unordered_set<int> hashKume = {5, 1, 3, 3, 1, 9};
    std::cout << "  unordered_set size = " << hashKume.size() << ", 9 var mi? " << hashKume.count(9) << "\n";

    // ------------------------------------------------------------ 6) Karşılaştırmalı özel sıralama
    std::cout << "\n--- 6) ters sirali map (std::greater) ---\n";
    std::map<int, std::string, std::greater<int>> ters;
    ters[1] = "bir";
    ters[3] = "uc";
    ters[2] = "iki";
    for (const auto& [k, deger] : ters) {
        std::cout << "  " << k << " = " << deger << "\n";
    }

    // ------------------------------------------------------------ 7) Hız karşılaştırması
    std::cout << "\n--- 7) hiz: 200000 ekleme + 200000 arama (-O2, bu makinede) ---\n";
    const int N = 200000;
    std::vector<int> anahtarlar;
    anahtarlar.reserve(N);
    for (int i = 0; i < N; ++i) {
        anahtarlar.push_back((i * 7919) % 1000003);     // karışık sıralı anahtarlar
    }
    auto olc = [&](auto& kap, const char* ad) {
        auto bas = std::chrono::steady_clock::now();
        for (int k : anahtarlar) {
            kap[k] = k;
        }
        long long toplam = 0;
        for (int k : anahtarlar) {
            toplam += kap.count(k);
        }
        auto son = std::chrono::steady_clock::now();
        std::cout << "  " << ad << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(son - bas).count()
                  << " ms (kontrol: bulunan = " << toplam << ")\n";
    };
    std::map<int, int> m;
    std::unordered_map<int, int> um;
    olc(m, "map           ");
    olc(um, "unordered_map ");
    std::cout << "  NOT: sureler makineye gore degisir; unordered_map genelde daha hizli (O(1) ortalama), map O(log n) ama sirali.\n";
    return 0;
}
