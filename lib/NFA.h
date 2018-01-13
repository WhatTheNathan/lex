//
// Created by Nathan on 14/12/2017.
//

#ifndef N_LEXER_NFA_H
#define N_LEXER_NFA_H

#include <vector>
#include <string>
#include <stack>
#include <set>
#include <map>

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
    NFA(std::string re, bool isletter);     //构造函数

    std::vector<int> terminalVec;           // 终态数组
    std::map<int,std::string> terminalMap;  // 结束状态-token映射表

    std::string tokenName;
    static int stateCount;                  //总状态数全局变量
    int headState;                          //开始状态
    int tailState;                          //未合并前结束状态
    std::vector<Triplet> triplets;          //三元组集合
    std::set<std::string> edges;            //边的集合
    std::stack<char> stack;                 //中缀转后缀所用栈
    void merge(std::vector<NFA> nfas);      // 合并两个nfa
    void printNFA();                        // 陈述NFA基本信息，调试使用
private:
    char firstLetter;                       // 用于[]的预处理识别
    char endLetter;
    std::string batchprocess(std::string re); // 分离/合并token
    std::string preprocess(std::string re);   // 预处理，目前并处理[]
    void adddot(std::string& re);             //对RE的连接加上.运算符

    // 先规定只有*,|,(,),.,+"运算符，优先级高的数字高
    // *的优先级大于| 大于.
    std::string infix2postfix(std::string re);
    int isp(char op);                       // 栈内优先级
    int icp(char op);                       // 入栈优先级

    void convert2nfa(std::string re);
    void mutiply();                         // *运算符
    void add();                             // +运算符
    void orr(NFA rightNFA);                 // |运算符
    void connect(NFA nfa);                  // .运算符
};

#endif //N_LEXER_NFA_H
