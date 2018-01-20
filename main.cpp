#include <iostream>
#include "lib/NFA.h"
#include "lib/DFA.h"
#include "lib/ODFA.h"
#include "re/RE.h"
#include "lib/Analyzer.h"

/*
 * 核心思想
 * 1.先实现lexer，自定义RE，然后将每个RE转成NFA(汤普森算法)
 * 2.将NFAs合成DFA
 * 3.再根据DFA对用户输入的字符序列分析出词法 (注意dfa所对应多个终态的解决方法)
 * 3'.自动根据DFA生成分析代码(Lex)
 * 4.根据输入的字符序列分析词法
 *
 * 完善: 增加更多re适配
 */
int main() {
    std::cout
            <<"    ***          *                              "<<'\n'
            <<"   ** **         *     ***   *   *   ***   * ***"<<'\n'
            <<"   *   *         *    *   *   * *   *   *  **   "<<'\n'
            <<"   *   * ------- *    *****    *    *****  *    "<<'\n'
            <<"   *   *         *    *       * *   *      *    "<<'\n'
            <<"   *   *          **   ****  *   *   ****  *    "<<std::endl;
    std::cout<<"building Lexical Analyzer based on RE.h...."<<std::endl;

    NFA digits_nfa = NFA(digits,false);
    NFA relop_nfa = NFA(sim_relop,false);
    NFA ws_nfa = NFA(ws, false);
    NFA main_nfa = NFA(final_id,false);

    std::vector<NFA> nfas;
    nfas.push_back(digits_nfa);
    nfas.push_back(relop_nfa);
    nfas.push_back(ws_nfa);

    main_nfa.merge(nfas);

//    main_nfa.printNFA();
    DFA dfa = DFA(main_nfa);
//    dfa.printDFA();
    ODFA odfa = ODFA(dfa);
//    odfa.printODFA();

    std::cout<<"build finished."<<std::endl;

//    std::string code = "if a01 > b10";
//    Analyzer analyzer = Analyzer(odfa,code);
//    analyzer.run();
    std::cout<<"Please enter you code"<<std::endl;
    std::string code;
    while(getline(std::cin,code)){
        Analyzer analyzer = Analyzer(odfa,code);
        analyzer.run();
        std::cout<<"Please enter you code"<<std::endl;
    }
    return 0;
}