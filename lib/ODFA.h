//
// Created by Nathan on 17/12/2017.
//

#ifndef N_LEXER_ODFA_H
#define N_LEXER_ODFA_H
#include "DFA.h"
#include <list>

struct OSet{
    std::set<std::set<int>> set;
    int judgeCount = 0;

    OSet(){}
    OSet(std::set<std::set<int>> _set, int _judgeCount){
        set = _set;
        judgeCount = _judgeCount;
    }

    bool isInSet(std::set<int> _set){
        for(auto temp: set){
            if(_set == temp){
                return true;
            }
        }
        return false;
    }

    bool operator <(const OSet& _oset) const{
        if(set.size()<_oset.set.size()){
            return true;
        }
        return false;
    }
};

struct OSetTriplet{
    std::set<std::set<int>> head;
    char edge;
    std::set<std::set<int>> tail;

    OSetTriplet(std::set<std::set<int>> _headSet,char _edge,std::set<std::set<int>> _tailSet){
        head = _headSet;
        edge = _edge;
        tail = _tailSet;
    }
};


class ODFA {
public:
    ODFA(DFA dfa);
    std::vector<OSet> sets;
    std::set<std::set<int>> headSet;
    std::vector<OSet> terminalSets; //包含终态的集合
    std::list<OSet> list;
    std::vector<OSetTriplet> oSetTriplets; //ODFA的三元组数组，表示优化后的状态集合的三元组关系
private:
    std::set<std::set<int>> emptySet;
    void optimization(DFA dfa); // 优化DFA
    void divideByTerminal(DFA dfa);
    void weakDivide(DFA dfa);
    void generateTriplet(DFA dfa);

    void printODFA(); //调试使用
};


#endif //N_LEXER_ODFA_H
