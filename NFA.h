//
// Created by Nathan on 14/12/2017.
//

#ifndef N_LEXER_NFA_H
#define N_LEXER_NFA_H

#include <stack>
#include <set>
#include <vector>
#include <string>
#include <iostream>

using namespace::std;

/**
 * @brief NFA的数据结构，以三元组表示图中的连接
 */
struct Triplet{
    char head;
    char edge;
    char tail;
};

class NFA {
public:
    vector<Triplet> nfa;
    NFA(string re);
};

#endif //N_LEXER_NFA_H
