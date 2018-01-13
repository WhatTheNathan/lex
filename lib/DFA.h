//
// Created by Nathan on 16/12/2017.
//

#ifndef N_LEXER_DFA_H
#define N_LEXER_DFA_H
#include <set>
#include "NFA.h"

struct SetTriplet{
    std::set<int> head;
    std::string edge;
    std::set<int> tail;

    SetTriplet(std::set<int> _head,std::string _edge,std::set<int> _tail){
        head = _head;
        edge = _edge;
        tail = _tail;
    }
};

class DFA {
public:
    DFA(NFA nfa);

    std::vector<int> terminalVec;                                   // 终态数组
    std::map<std::set<int>,std::string> setTerminal_TokenMap;       // 结束状态集合-token映射表
    std::map<int,std::string> terminalMap;                          // 结束状态-token映射表

    std::vector<std::set<int>> sets;
    std::set<int> headSet;
    std::vector<SetTriplet> setTriplets;                            //DFA的三元组数组，表示合并后的状态集合的三元组关系
    std::vector<Triplet> triplets;                                  //NFA的三元组数组,具体的未合并的状态的三元组关系
    std::set<std::string> edges;                                    //边的集合
    int endState;                                                   // NFA的结束状态
    std::set<int> move(std::set<int> states,std::string edge);      // edge转换
    std::set<int> e_closure(std::set<int> states);                  // e传递闭包
    // 1~n 为所属终结状态的编号
    // 0则不为终结状态
    int setOrder(std::set<int> _set);
    void printDFA();
private:
    void determined(NFA nfa);                                       // 确定化
    bool isSetExist(std::set<int> _set);                            //判断该状态集合是否已存在
    void judgeTerminal(std::set<int> _set);
};


#endif //N_LEXER_DFA_H