// Konu: Thread-safe sayaç: data race'i görmek ve mutex / atomic ile çözmek
// Ne gösteriyor: 4 thread aynı sayacı 100000'er kez artırınca korumasız sonucun bozulmasını; mutex, atomic ve yerel toplama çözümlerini.
// Neden önemli: Eşzamanlılık mülakatının klasik canlı kodlama sorusu: "data race nedir, nasıl önlersin, mutex ile atomic farkı?"
// Derleme: g++ -std=c++17 -Wall -Wextra -pthread -o 45_thread_safe_sayac 45_thread_safe_sayac.cpp

#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

constexpr int THREAD_SAYISI = 4;
constexpr int ADIM = 100000;

// Aynı işi THREAD_SAYISI thread'de çalıştırır, bitmesini bekler (join), geçen süreyi ms olarak döner.
template <typename Is>
long long calistir(Is is) {
    auto bas = std::chrono::steady_clock::now();
    std::vector<std::thread> isParcaciklari;
    for (int t = 0; t < THREAD_SAYISI; ++t) {
        isParcaciklari.emplace_back(is);
    }
    for (auto& th : isParcaciklari) {
        th.join();
    }
    auto son = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(son - bas).count();
}

// 1) KORUMASIZ: ++ tek bir işlem gibi görünür ama aslında "oku, artır, yaz" üç adımdır.
//    İki thread aynı değeri okuyup aynı sonucu yazarsa bir artış KAYBOLUR. Bu bir DATA RACE = tanımsız davranış.
int korumasiz = 0;

// 2) MUTEX: aynı anda yalnızca bir thread kritik bölgeye (kilit altındaki kod) girer.
int mutexli = 0;
std::mutex kilit;

// 3) ATOMIC: artırma işlemi bölünemez (donanım düzeyinde tek adım), kilit gerekmez.
std::atomic<int> atomikSayac{0};

// 4) YEREL TOPLAMA: her thread kendi yerel sayacını artırır, sonda TEK SEFER kilit alıp ekler (kilit maliyeti ~yok).
int yerelToplam = 0;

int main() {
    const int beklenen = THREAD_SAYISI * ADIM;
    std::cout << "beklenen sonuc = " << beklenen << " (" << THREAD_SAYISI << " thread x " << ADIM << ")\n\n";

    long long ms = calistir([] {
        for (int i = 0; i < ADIM; ++i) {
            ++korumasiz;
        }
    });
    std::cout << "1) korumasiz : " << korumasiz << (korumasiz == beklenen ? " (bu sefer tutti, ama GARANTI YOK)" : "  <- YANLIS, artislar kayboldu (data race)")
              << "   [" << ms << " ms]\n";

    ms = calistir([] {
        for (int i = 0; i < ADIM; ++i) {
            std::lock_guard<std::mutex> koruma(kilit);   // kapsam bitince kilit otomatik açılır (RAII)
            ++mutexli;
        }
    });
    std::cout << "2) mutex     : " << mutexli << (mutexli == beklenen ? "  dogru" : "  YANLIS") << "   [" << ms << " ms]\n";

    ms = calistir([] {
        for (int i = 0; i < ADIM; ++i) {
            ++atomikSayac;
        }
    });
    std::cout << "3) atomic    : " << atomikSayac << (atomikSayac == beklenen ? "  dogru" : "  YANLIS") << "   [" << ms << " ms]\n";

    ms = calistir([] {
        int yerel = 0;
        for (int i = 0; i < ADIM; ++i) {
            ++yerel;
        }
        std::lock_guard<std::mutex> koruma(kilit);
        yerelToplam += yerel;
    });
    std::cout << "4) yerel+kilit: " << yerelToplam << (yerelToplam == beklenen ? "  dogru" : "  YANLIS") << "   [" << ms << " ms]\n";

    std::cout << "\nNOT: sureler makineye gore degisir; korumasiz sonuc her calistirmada farkli cikabilir.\n";
    return 0;
}
