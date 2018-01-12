#include <iostream>
#include "lib/NFA.h"
#include "lib/DFA.h"
#include "lib/ODFA.h"
#include "re/RE.h"
#include "lib/Analyzer.h"

/*
 * 核心思想
 * 1.先实现lexer，自定义RE，然后将每个RE转成NFA(汤普森算法)
 * 2.将NFAs合成DFA (研究合并优化后的DFA的终结状态对应多个RE的判断情况)
 * 3.再根据DFA对用户输入的字符序列分析出词法
 * 3'.自动根据DFA生成分析代码(Lex)
 * 4.根据输入的字符序列分析词法
 */
int main() {
//    std::string re = "test->(a*b)*(a|b)";
    std::string re = "digits->[0-9]+";

    NFA nfa = NFA(re,false);
    DFA dfa = DFA(nfa);
    ODFA odfa = ODFA(dfa);

    std::string code = "321";
    Analyzer analyzer = Analyzer(odfa,code);
    analyzer.run();


    return 0;
}