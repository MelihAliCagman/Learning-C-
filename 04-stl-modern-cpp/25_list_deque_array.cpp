// Konu: vector, list, deque ve array karşılaştırması: hangisi ne zaman?
// Ne gösteriyor: Baştan ekleme maliyetini, iterator kararlılığını, bellek düzenini (sizeof) ve rastgele erişimi; her konteynerin güçlü/zayıf yanını ölçümle.
// Neden önemli: "vector, list, deque, array ne zaman hangisi?" STL mülakatının üçüncü klasik sorusu; cevap "ölç ve düşün" olmalı.
// Derleme: g++ -std=c++17 -Wall -Wextra -O2 -o 25_list_deque_array 25_list_deque_array.cpp

#include <array>
#include <chrono>
#include <deque>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

template <typename Is>
long long olc(Is is) {
    auto bas = std::chrono::steady_clock::now();
    is();
    auto son = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(son - bas).count();
}

int main() {
    // ------------------------------------------------------------ 1) array: sabit boyut, heap yok
    std::cout << "--- 1) std::array: boyut derleme zamaninda sabit ---\n";
    std::array<int, 5> a = {5, 3, 8, 1, 9};
    std::array<int, 5> b = a;                         // atama/kopya mümkün (C dizisinde değil)
    b[0] = 100;
    std::cout << "  a.size() = " << a.size() << ", sizeof(a) = " << sizeof(a) << " (5 x 4 bayt, HEAP YOK)\n";
    std::cout << "  a == b ? " << (a == b) << ", a[0] = " << a[0] << ", b[0] = " << b[0] << " (kopya bagimsiz)\n";
    a.fill(7);
    std::cout << "  fill(7) sonrasi a[2] = " << a[2] << ", a.at(4) = " << a.at(4) << "\n";

    // ------------------------------------------------------------ 2) list: iterator kararlılığı
    std::cout << "\n--- 2) std::list: arada ekleme/silme, iterator KARARLI ---\n";
    std::list<int> l = {1, 2, 3, 4, 5};
    auto it = l.begin();
    std::advance(it, 2);                              // 3'ü gösterir
    l.insert(it, 99);                                 // 3'ün ÖNÜNE ekle: O(1), diğer elemanlar kaymaz
    l.push_front(0);
    l.erase(std::next(l.begin()));                    // 2. elemanı sil
    std::cout << "  it hala " << *it << "'u gosteriyor (ekleme/silme sonrasi gecerli)  liste: ";
    for (int x : l) {
        std::cout << x << " ";
    }
    std::cout << "\n  l.sort() ile siralama (list'in KENDI sort'u, std::sort calismaz): ";
    l.sort();
    for (int x : l) {
        std::cout << x << " ";
    }
    std::cout << "\n  list[2] YOK: rastgele erisim yok (operator[] tanimli degil), gezinerek ulasilir: O(n)\n";

    // ------------------------------------------------------------ 3) deque: iki uçtan O(1)
    std::cout << "\n--- 3) std::deque: iki uctan O(1) ekleme + rastgele erisim ---\n";
    std::deque<int> d = {3, 4};
    d.push_front(2);
    d.push_front(1);
    d.push_back(5);
    std::cout << "  deque: ";
    for (int x : d) {
        std::cout << x << " ";
    }
    std::cout << "  d[2] = " << d[2] << " (rastgele erisim O(1) var)\n";
    std::cout << "  NOT: deque parcali bloklarda tutulur: bellekte tek ardisik blok DEGILDIR (&d[0] + 1 == &d[1] garanti degil).\n";

    // ------------------------------------------------------------ 4) boyutlar
    std::cout << "\n--- 4) sizeof (bu derleyicide, bos nesne) ---\n";
    std::cout << "  array<int,5> = " << sizeof(std::array<int, 5>) << ", vector<int> = " << sizeof(std::vector<int>)
              << ", list<int> = " << sizeof(std::list<int>) << ", deque<int> = " << sizeof(std::deque<int>) << "\n";
    std::cout << "  NOT: list her eleman icin ayri dugum ayirir (2 pointer + deger = ~24 bayt/int), vector ardisik 4 bayt/int.\n";

    // ------------------------------------------------------------ 5) Hız: başa ekleme
    std::cout << "\n--- 5) 20000 elemani BASA ekleme (-O2, mikrosaniye, bu makinede) ---\n";
    const int N = 20000;
    long long tv = olc([&] { std::vector<int> v; for (int i = 0; i < N; ++i) v.insert(v.begin(), i); });
    long long tl = olc([&] { std::list<int> li; for (int i = 0; i < N; ++i) li.push_front(i); });
    long long td = olc([&] { std::deque<int> de; for (int i = 0; i < N; ++i) de.push_front(i); });
    std::cout << "  vector.insert(begin) : " << tv << " us   (her ekleme tum elemanlari kaydirir: O(n) -> toplam O(n^2))\n";
    std::cout << "  list.push_front      : " << tl << " us\n";
    std::cout << "  deque.push_front     : " << td << " us\n";

    // ------------------------------------------------------------ 6) Hız: gezme (cache etkisi)
    std::cout << "\n--- 6) 1.000.000 elemani toplama (gezme) ---\n";
    const int M = 1000000;
    std::vector<int> v(M, 1);
    std::list<int> li(M, 1);
    std::deque<int> de(M, 1);
    long long s1 = 0, s2 = 0, s3 = 0;
    long long gv = olc([&] { s1 = std::accumulate(v.begin(), v.end(), 0LL); });
    long long gl = olc([&] { s2 = std::accumulate(li.begin(), li.end(), 0LL); });
    long long gd = olc([&] { s3 = std::accumulate(de.begin(), de.end(), 0LL); });
    std::cout << "  vector: " << gv << " us, list: " << gl << " us, deque: " << gd << " us   (toplamlar: " << s1 << " " << s2 << " " << s3 << ")\n";
    std::cout << "  NOT: vector ardisik bellek (cache dostu) oldugu icin gezmede genelde en hizli; list dugumleri bellekte dagilir.\n";
    return 0;
}
