//
// Created by Nathan on 16/12/2017.
//

#ifndef N_LEXER_DFA_H
#define N_LEXER_DFA_H
#include <vector>
#include <queue>
#include <set>
#include "NFA.h"

struct StateTriplet{
    std::set<int> head;
    char edge;
    std::set<int> tail;

    StateTriplet(std::set<int> _head,char _edge,std::set<int> _tail){
        head = _head;
        edge = _edge;
        tail = _tail;
    }
};

class DFA {
public:
    DFA(NFA nfa);
    std::vector<std::set<int>> stateSet;
    std::set<int> headState;
    std::set<int> tailState;
    std::vector<Triplet> triplets; //三元组集合,具体的未合并的状态的三元组关系
    static int stateCount;
private:
    void determined(); // 确定化
    void move(char edge); // edge转换
    void e_closure(); // e传递闭包
};


#endif //N_LEXER_DFA_H
