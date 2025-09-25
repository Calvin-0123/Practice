#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    cout << "请输入表达式（例如：2*20 + 3*10 - 5/2）: ";
    string s;
    getline(cin, s);

    long long total = 0;
    long long term  = 0;
    long long num   = 0;
    char lastOp = '+';

    auto apply = [&](char op, long long value) {
        switch (op) {
            case '+':
                total += term;
                term = value;
                break;
            case '-':
                total += term;
                term = -value;
                break;
            case '*':
                term = term * value;
                break;
            case '/':
                if (value == 0) {
                    cout << "错误：除数为 0" << endl;
                    exit(1);
                }
                term = term / value;
                break;
        }
    };

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (isspace(static_cast<unsigned char>(c))) continue;

        if (isdigit(static_cast<unsigned char>(c))) {
            num = c - '0';
            while (i + 1 < s.size() && isdigit(static_cast<unsigned char>(s[i + 1]))) {
                num = num * 10 + (s[++i] - '0');
            }
            apply(lastOp, num);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            lastOp = c;
        } else {
            cout << "错误：不支持的字符 '" << c << "'" << endl;
            return 1;
        }
    }

    long long result = total + term;
    cout << "结果: " << result << endl;
    return 0;
}