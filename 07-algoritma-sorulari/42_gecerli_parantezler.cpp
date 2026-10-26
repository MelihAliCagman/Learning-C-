// Konu: Geçerli parantezler (valid parentheses): (), [] ve {} doğru sırada ve eşli mi?
// Ne gösteriyor: Stack (yığın) veri yapısıyla "son açılan ilk kapanır" kuralını; her kapanışta en son açılanla eşleşmeyi.
// Neden önemli: Stack kullanımının en klasik mülakat örneği (derleyiciler ve ifade çözücüler böyle çalışır).
// Derleme: g++ -std=c++17 -Wall -Wextra -o 42_gecerli_parantezler 42_gecerli_parantezler.cpp

#include <iostream>
#include <stack>
#include <string>

bool eslesirMi(char acilis, char kapanis) {
    return (acilis == '(' && kapanis == ')') || (acilis == '[' && kapanis == ']') || (acilis == '{' && kapanis == '}');
}

// O(n) zaman, O(n) bellek (en kötü durumda hepsi açılış parantezi).
// Açılışı stack'e at; kapanış gelince stack'in tepesiyle eşleşmeli. Sonda stack boş olmalı.
bool gecerliMi(const std::string& s) {
    std::stack<char> yigin;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            yigin.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (yigin.empty() || !eslesirMi(yigin.top(), c)) {
                return false;                  // eşleşecek açılış yok ya da yanlış tür
            }
            yigin.pop();
        }
        // diğer karakterleri (harf, rakam, boşluk) yok sayıyoruz
    }
    return yigin.empty();                      // kapanmamış açılış kaldıysa geçersiz
}

int main() {
    for (std::string s : {"()[]{}", "([{}])", "(]", "((", "", "())", "{[}]", "a(b[c]{d})e", ")("}) {
        std::cout << "\"" << s << "\" -> " << (gecerliMi(s) ? "gecerli" : "gecersiz") << "\n";
    }
    return 0;
}
