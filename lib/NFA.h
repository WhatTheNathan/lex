//
// Created by Nathan on 14/12/2017.
//

#ifndef N_LEXER_NFA_H
#define N_LEXER_NFA_H

#include <vector>
#include <string>
#include <stack>
#include <set>

/**
 * @brief NFA的数据结构，以三元组表示图中的连接
 */
struct Triplet{
    int head;
    std::string edge;
    int tail;

    Triplet(int _head,std::string _edge,int _tail){
        head = _head;
        edge = _edge;
        tail = _tail;
    }
};

class NFA {
public:
    NFA(std::string re, bool isletter); //构造函数

    static int stateCount;          //总状态数全局变量
    int headState;                   //开始状态
    int tailState;                  //结束状态
    std::vector<Triplet> triplets;   //三元组集合
    std::set<std::string> edges;
    std::stack<char> stack;         //中缀转后缀所用栈

    void printNFA(); // 陈述NFA基本信息，调试使用
private:
    // 用于[]的预处理识别
    char firstLetter;
    char endLetter;
    void preprocess(std::string& re); // 预处理，目前处理[]
    void adddot(std::string& re);  //对RE的连接加上.运算符

    // 先规定只有*,|,(,),.,+"运算符，优先级高的数字高
    // *的优先级大于| 大于.
    std::string infix2postfix(std::string re);
    int isp(char op); // 栈内优先级
    int icp(char op); // 入栈优先级

    void convert2nfa(std::string re);
    void mutiply();
    void add();
    void orr(NFA rightNFA);
    void connect(NFA nfa);
};

#endif //N_LEXER_NFA_H
