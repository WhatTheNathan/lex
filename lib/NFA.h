//
// Created by Nathan on 14/12/2017.
//

#ifndef N_LEXER_NFA_H
#define N_LEXER_NFA_H

#include <vector>
#include <string>
#include <stack>

/**
 * @brief NFA的数据结构，以三元组表示图中的连接
 */
struct Triplet{
    int head;
    char edge;
    int tail;

    Triplet(int _head,int _edge,int _tail){
        head = _head;
        edge = _edge;
        tail = _tail;
    }
};

class NFA {
public:
    int headState;                 //开始状态
    int tailSate;                  //结束状态
    std::vector<Triplet> triplets; //三元组集合
    std::stack<char> stack;       //中缀转后缀所用栈
    std::stack<NFA> subnfa_stack; // 子NFA的栈
    NFA(std::string re); //构造函数
    NFA(char letter);    //构造函数
    static int stateCount = 0;    //总状态数全局变量
private:
    void adddot(std::string& re);  //对RE的连接加上.运算符

    // 先规定只有*,|,(,),."这五种运算符，优先级高的数字高
    // *的优先级大于| 大于.
    std::string infix2postfix(std::string re);

    void convert2nfa(std::string re);
    NFA mutiplySubNFA(NFA nfa);   //
    NFA orSubNFA(NFA leftNFA, NFA rightNFA);
    NFA connectSubNFA(NFA leftNFA, NFA rightNFA);
    // 栈内优先级
    int isp(char op);
    // 入栈优先级
    int icp(char op);
};

#endif //N_LEXER_NFA_H
