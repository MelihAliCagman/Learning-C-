// Konu: FizzBuzz (3'e bölünürse Fizz, 5'e bölünürse Buzz, ikisine de bölünürse FizzBuzz)
// Ne gösteriyor: Koşul sırasının önemini: "ikisine de bölünür" durumu önce kontrol edilmeli.
// Neden önemli: Mülakatların en ünlü ısınma sorusu; kod okuma ve koşul sırası bilgisini ölçer.
// Derleme: g++ -std=c++17 -Wall -Wextra -o 15_fizzbuzz 15_fizzbuzz.cpp

#include <iostream>
#include <string>

std::string fizzBuzz(int n) {
    if (n % 15 == 0) {            // önce en özel durum (3'e VE 5'e bölünür)
        return "FizzBuzz";
    }
    if (n % 3 == 0) {
        return "Fizz";
    }
    if (n % 5 == 0) {
        return "Buzz";
    }
    return std::to_string(n);
}

int main() {
    for (int i = 1; i <= 30; ++i) {
        std::cout << fizzBuzz(i) << (i < 30 ? " " : "\n");
    }
    std::cout << "NOT: n % 3 kontrolunu one alirsan 15 icin 'Fizz' yazar: sira onemli.\n";
    return 0;
}
