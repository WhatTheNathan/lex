#include <iostream>

/*
 * 核心思想
 * 1.先实现lexer，自定义RE，然后将每个RE转成NFA(汤普森算法)
 * 2.将NFAs合成DFA
 * 3.再根据DFA对用户输入的字符序列分析出词法
 * 3'.自动根据DFA生成分析代码(Lex)
 * 4.根据输入的字符序列分析词法
 */
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}