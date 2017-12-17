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
    int tailState;                  //结束状态
    std::vector<Triplet> triplets; //三元组集合
    std::stack<char> stack;       //中缀转后缀所用栈
    NFA(std::string re); //构造函数
    NFA(char letter);    //构造函数

    static int stateCount;    //总状态数全局变量

    void printNFA(); // 陈述NFA基本信息，调试使用
private:
    void adddot(std::string& re);  //对RE的连接加上.运算符

    // 先规定只有*,|,(,),."这五种运算符，优先级高的数字高
    // *的优先级大于| 大于.
    std::string infix2postfix(std::string re);

    void convert2nfa(std::string re);
    void mutiply();
    void orr(NFA rightNFA);
    void connect(NFA nfa);
    int isp(char op); // 栈内优先级
    int icp(char op); // 入栈优先级
};

#endif //N_LEXER_NFA_H
