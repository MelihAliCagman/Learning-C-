# Learning C++

C++ öğrenme notlarım ve örneklerim. Her örnek tek bir `.cpp` dosyasıdır ve üstünde "ne gösteriyor, neden böyle" açıklaması bulunur. Amaç; temelden başlayıp sistem, ağ ve robotik yazılımlarında kullanılan konulara kadar ilerlemek.

> Not: Bu repo bir öğrenme günlüğüdür. Örnekler zamanla eklenir ve güncellenir; durumu aşağıdaki listeden takip edebilirsiniz.

## Derleme ve çalıştırma

Tek dosya için:

```bash
g++ -std=c++17 -Wall -Wextra -o ornek ornek.cpp
./ornek
```

Thread kullanan örneklerde `-pthread` eklenir:

```bash
g++ -std=c++17 -Wall -Wextra -pthread -o ornek ornek.cpp
```

Bellek hatalarını yakalamak için (isteğe bağlı):

```bash
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -o ornek ornek.cpp
```

Windows'ta PowerShell'de çalıştırma: `.\ornek.exe`

## Klasör yapısı

```
Learning-C++/
├── README.md
├── 01-temeller/
├── 02-bellek-raii/
├── 03-siniflar-oop/
├── 04-stl-modern-cpp/
├── 05-eszamanlilik/
├── 06-ag-ve-sistem/
├── 07-algoritma-sorulari/
├── 08-mini-projeler/
└── notlar/                (her oturumun soru ve cevap notları, PDF)
```

## Konu listesi ve durum

Tamamlanan örnekler işaretlenir. Her satır bir `.cpp` dosyasına karşılık gelir.

### 01 - Dil temelleri
- [ ] Veri tipleri, `sizeof`, sabit genişlikli tipler (`int32_t`, `uint8_t`)
- [ ] Signed/unsigned, taşma (overflow), tip dönüşümleri
- [x] `const` çeşitleri (`const int*` / `int* const`): [`01-temeller/02_const_pointer.cpp`](01-temeller/02_const_pointer.cpp)
- [ ] Scope, ömür ve `static` kullanımları
- [ ] Operatörler (`++i` / `i++`, mantıksal, bit düzeyi)
- [ ] Bit işlemleri (set / clear / toggle / maske)
- [ ] `enum class`, `struct` ve `class` farkı, `constexpr`, `auto`
- [ ] Fonksiyonlar: değer/referans/pointer ile geçirme, overloading, varsayılan argüman (kısmen: [`03_const_ref.cpp`](01-temeller/03_const_ref.cpp))
- [ ] Dizi ve pointer ilişkisi, pointer aritmetiği
- [ ] C tarzı string ve `std::string`
- [ ] Header / source ayrımı, include guard, `namespace`
- [ ] Tanımsız davranış örnekleri

### 02 - Bellek ve RAII
- [ ] Pointer ve referans farkı
- [ ] Stack ve heap
- [ ] `new` / `delete`, `new[]` / `delete[]`, bellek sızıntısı
- [ ] Dangling pointer, double free, use-after-free
- [ ] RAII fikri
- [ ] `unique_ptr`
- [ ] `shared_ptr` ve `weak_ptr`

### 03 - Sınıflar ve OOP
- [ ] Constructor çeşitleri, initializer list, destructor
- [ ] Kopyalama ve taşıma (Rule of 3/5/0)
- [ ] `virtual`, `override`, soyut sınıf, sanal destructor
- [ ] Kalıtım ve kompozisyon
- [ ] `static` üyeler, `friend`, `explicit`
- [ ] Operatör aşırı yükleme

### 04 - STL ve modern C++
- [ ] `vector` (size / capacity, reallocation, iterator geçersizleşmesi)
- [ ] `map` / `unordered_map` / `set`
- [ ] `list`, `deque`, `array` karşılaştırması
- [ ] `queue`, `stack`, `priority_queue`
- [ ] Iterator'lar ve `<algorithm>`
- [ ] Lambda ve capture, `std::function`
- [ ] Şablonlar (template) temelleri
- [ ] İstisnalar (exception)
- [ ] `optional`, `string_view`, dosya G/Ç

### 05 - Eşzamanlılık
- [ ] `thread` ve `join`
- [ ] Data race ve `mutex` / `lock_guard`
- [ ] `std::atomic`
- [ ] `condition_variable` ve üretici-tüketici kuyruğu
- [ ] Deadlock örneği ve çözümü

### 06 - Ağ ve sistem
- [ ] Basit UDP gönderici / alıcı
- [ ] Basit TCP istemci / sunucu

### 07 - Algoritma soruları
- [x] swap (pointer ve referans): [`01-temeller/01_swap.cpp`](01-temeller/01_swap.cpp)
- [ ] String ters çevirme, palindrom
- [ ] En büyük / en küçük eleman
- [ ] Fibonacci, faktöriyel, asal kontrolü
- [ ] Kelime sıklığı (`unordered_map`)
- [ ] İkili arama, basit sıralama
- [ ] Bağlı liste ters çevirme

### 08 - Mini projeler
- [ ] Thread-safe telemetri kuyruğu
- [ ] Basit durum makinesi

## Örnek dosya şablonu

```cpp
// Konu: <kısa başlık>
// Ne gösteriyor: <bir iki cümle>
// Neden önemli: <bir iki cümle>
// Derleme: g++ -std=c++17 -Wall -Wextra -o ornek ornek.cpp

#include <iostream>

int main() {
    // kod
}
```

## Çalışma kuralları

- Kodu elle yazıyorum, derliyorum ve çalıştırıp sonucu gözlemliyorum.
- Açıklamaları kendi cümlelerimle yazıyorum.
- Her örnek için anlamlı bir commit mesajı atıyorum (ör. `Add unique_ptr example`).
- Anlamadığım yerleri yorum satırında `TODO:` ile işaretleyip sonra geri dönüyorum.

## Yol haritası

C++ temelleri → bellek ve RAII → sınıflar → STL → eşzamanlılık → ağ programlama → ROS 2 ile C++ node'ları (ayrı bir repoda).

## İletişim

GitHub: [MelihAliCagman](https://github.com/MelihAliCagman)
