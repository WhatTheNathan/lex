//
// Created by Nathan on 14/12/2017.
//

#ifndef N_LEXER_NFA_H
#define N_LEXER_NFA_H

#include <vector>
#include <string>

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
    std::vector<Triplet> nfa;

    NFA(std::string re);

private:
    std::string adddot(std::string re);

    // 先规定只有*,|,(,),."这四种运算符，优先级高的数字高
    // *的优先级大于| 大于.
    std::string infix2postfix(std::string re);
    // 栈内优先级
    int isp(char op);
    // 入栈优先级
    int icp(char op);
};

#endif //N_LEXER_NFA_H
