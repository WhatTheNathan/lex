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
    NFA digits_nfa = NFA(digits,false);
    NFA test_nfa = NFA(re, false);

    std::vector<NFA> nfas;
    nfas.push_back(test_nfa);
    digits_nfa.merge(nfas);
    digits_nfa.printNFA();

    DFA dfa = DFA(digits_nfa);
    ODFA odfa = ODFA(dfa);

    std::string code = "21312";
    Analyzer analyzer = Analyzer(odfa,code);
    analyzer.run();


    return 0;
}