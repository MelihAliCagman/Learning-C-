// Konu: İki stack ile kuyruk (queue) gerçekleştirmek
// Ne gösteriyor: Son giren ilk çıkar (stack) yapısını iki tane kullanıp ilk giren ilk çıkar (kuyruk) davranışı elde etmeyi; amortize O(1) maliyeti.
// Neden önemli: Veri yapısı mülakatlarının en sevilen sorusu; "amortize maliyet nedir?" takibi gelir.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 46_iki_stack_ile_kuyruk 46_iki_stack_ile_kuyruk.cpp

#include <cstddef>
#include <iostream>
#include <stack>

// Fikir: giris_ yığınına eklenir. Çıkarma gerektiğinde cikis_ BOŞSA giris_'in tüm elemanları cikis_'e aktarılır
// (sıra tersine döner: son giren üste, ilk giren en üste gelir). cikis_'in tepesi kuyruğun başıdır.
class KuyrukIkiStack {
    std::stack<int> giris_;
    std::stack<int> cikis_;
    long long aktarimSayisi_ = 0;     // toplam kaç eleman taşındı (amortize analizi için)

    void aktar() {
        if (cikis_.empty()) {         // yalnızca cikis_ boşken aktar: aksi hâlde sıra bozulur
            while (!giris_.empty()) {
                cikis_.push(giris_.top());
                giris_.pop();
                ++aktarimSayisi_;
            }
        }
    }

public:
    void ekle(int x) {                // O(1)
        giris_.push(x);
    }

    bool cikar(int& x) {              // amortize O(1)
        aktar();
        if (cikis_.empty()) {
            return false;             // kuyruk boş
        }
        x = cikis_.top();
        cikis_.pop();
        return true;
    }

    bool bastaki(int& x) {            // kuyruğun başındaki elemanı çıkarmadan okur
        aktar();
        if (cikis_.empty()) {
            return false;
        }
        x = cikis_.top();
        return true;
    }

    bool bosMu() const { return giris_.empty() && cikis_.empty(); }
    std::size_t boyut() const { return giris_.size() + cikis_.size(); }
    long long aktarimSayisi() const { return aktarimSayisi_; }
};

int main() {
    KuyrukIkiStack k;
    std::cout << "ekle: 1 2 3\n";
    k.ekle(1);
    k.ekle(2);
    k.ekle(3);

    int x = 0;
    k.cikar(x);
    std::cout << "cikar -> " << x << "  (ilk giren ilk cikar)\n";

    std::cout << "ekle: 4\n";
    k.ekle(4);
    k.bastaki(x);
    std::cout << "bastaki -> " << x << ", boyut = " << k.boyut() << "\n";

    std::cout << "kalanlari cikar: ";
    while (k.cikar(x)) {
        std::cout << x << " ";
    }
    std::cout << "\nbos kuyruktan cikar -> " << (k.cikar(x) ? "eleman geldi" : "false (bos)") << ", bosMu = " << k.bosMu() << "\n";

    // Amortize analiz: 1000 ekle + 1000 çıkar. Her eleman en fazla BİR kez aktarılır.
    KuyrukIkiStack buyuk;
    for (int i = 0; i < 1000; ++i) {
        buyuk.ekle(i);
    }
    int toplam = 0;
    while (buyuk.cikar(x)) {
        toplam += x;
    }
    std::cout << "\n1000 ekle + 1000 cikar: toplam aktarim = " << buyuk.aktarimSayisi() << "  (eleman basina 1: amortize O(1))\n";
    std::cout << "(kontrol: cikan elemanlarin toplami = " << toplam << ")\n";
    return 0;
}
