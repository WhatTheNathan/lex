//
// Created by Nathan on 16/12/2017.
//

#ifndef N_LEXER_DFA_H
#define N_LEXER_DFA_H
#include <set>
#include "NFA.h"

struct SetTriplet{
    std::set<int> head;
    char edge;
    std::set<int> tail;

    SetTriplet(std::set<int> _head,char _edge,std::set<int> _tail){
        head = _head;
        edge = _edge;
        tail = _tail;
    }
};

class DFA {
public:
    DFA(NFA nfa);
    std::vector<std::set<int>> sets;
    std::set<int> headSet;
    std::vector<std::set<int>> terminalSets;        //包含终态的集合

    std::vector<SetTriplet> setTriplets;        //DFA的三元组数组，表示合并后的状态集合的三元组关系
    std::vector<Triplet> triplets;              //NFA的三元组数组,具体的未合并的状态的三元组关系

    int endState;                               // NFA的结束状态

    std::set<int> move(std::set<int> states,char edge); // edge转换
    std::set<int> e_closure(std::set<int> states);      // e传递闭包
    bool isTerminal(std::set<int> _set);
private:
    void determined(NFA nfa);                              // 确定化
    bool isSetExist(std::set<int> _set);                //判断该状态集合是否已存在
    void judgeTerminal(std::set<int> _set);
    void printDFA();
};


#endif //N_LEXER_DFA_H
