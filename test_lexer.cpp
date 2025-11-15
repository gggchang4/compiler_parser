#include "lexer.h"
#include <iostream>
using namespace std;
int main() {
    string input = R"(// 鏂愭尝閭ｅ鏁板垪璁＄畻锛堥€掑綊瀹炵幇锛?int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

// 鏈€澶у叕绾︽暟锛堣緱杞浉闄ゆ硶锛?int gcd(int a, int b)";
    Lexer lexer(input);
    vector<Token> tokens = lexer.getAllTokens();
    for (int i = 0; i < min(10, (int)tokens.size()); i++) {
        cout << tokens[i].index << ":" << tokens[i].line << ":" << typeToStr(tokens[i].type) << ":" << tokens[i].value << endl;
    }
    return 0;
}
