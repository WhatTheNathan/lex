//
// Created by Nathan on 14/12/2017.
//

#include "NFA.h"
#include <stack>
#include <iostream>

using namespace::std;

NFA::NFA(std::string re) {
    adddot(re);
    string postfixRE = infix2postfix(re);
}

NFA::NFA(char letter) {
    headState = ++stateCount;
    tailSate = ++stateCount;
    Triplet triple = Triplet(headState,letter,tailSate);
}

void NFA::adddot(std::string& re) {
    for(int i=0; i<re.size(); i++){
        if( ( (re[i] == ')') || (re[i] == '*')) && ((i+1) != re.size() && re[i+1] != '*')) {
            re.insert(i+1,".");
        }
    }
}

string NFA::infix2postfix(string re) {
    string postfixRE = "";
    stack.push('#');
    for(int i=0; i<re.size(); i++){
//        cout<<re[i]<<endl;
//        cout<<postfixRE<<endl;
        if(re[i] == '(' || re[i] == '*' || re[i] == '|' || re[i] == '.'){
            // 运算符优先级高的入栈; 比栈中低，则栈中运算符出栈
            if(icp(re[i]) > isp(stack.top()))
                stack.push(re[i]);
            else{
                postfixRE = postfixRE + stack.top();
                stack.pop();
                stack.push(re[i]);
            }
        }
        // 若遍历到)运算符，则匹配栈中的(运算符
        else if(re[i] == ')') {
            while(stack.top()!='('){
                if(stack.top() == '#')
                    cout<<"error occur"<<endl;
                postfixRE = postfixRE + stack.top();
                stack.pop();
            }
            stack.pop();
        }
        // 若为操作数
        else{
            postfixRE = postfixRE + re[i];
        }
    }
    // 将栈中剩余操作符弹出
    while(stack.top() != '#'){
        postfixRE = postfixRE + stack.top();
        stack.pop();
    }
    return postfixRE;
}

// 需要一个构造*运算符的子函数和一个构造|运算符的子函数
// 操作数可以构造一个子NFA，然后入栈
// 遇到*运算符则对栈顶NFA构造新*型NFA
// 遇到.运算符则对栈顶NFA构造新.型NFA
// 遇到|运算符则对栈顶NFA构造新|型NFA
void NFA::convert2nfa(std::string re) {
    for(int i=0; i<re.size(); i++){
        // 先简陋地使用a或b，之后使用字母的集合
        if(re[i] == 'a' || re[i] == 'b'){
            NFA subnfa = NFA(re[i]);
            subnfa_stack.push(subnfa);
        }
        else if(re[i] == '*'){
            NFA subnfa = mutiplySubNFA(subnfa_stack.top());
            subnfa_stack.pop();
            subnfa_stack.push(subnfa);
        }
        else if(re[i] == '|'){
            NFA sub_right_nfa = subnfa_stack.top();
            subnfa_stack.pop();
            NFA sub_left_nfa = subnfa_stack.top();
            subnfa_stack.pop();
            NFA subnfa = orSubNFA(sub_left_nfa,sub_right_nfa);
            subnfa_stack.push(subnfa);
        }
        else if(re[i] == '.'){

        }
    }
}

NFA NFA::mutiplySubNFA(NFA nfa) {

}

NFA NFA::orSubNFA(NFA leftNFA, NFA rightNFA) {

}

NFA NFA::connectSubNFA(NFA leftNFA, NFA rightNFA) {

}

int NFA::isp(char op) {
    switch(op){
        case '*':
            return 4;
        case '.':
            return 2;
        case '|':
            return 3;
        case '(':
            return 0;
        case '#':
            return 0;
    }
}

int NFA::icp(char op) {
    switch(op){
        case '*':
            return 4;
        case '.':
            return 2;
        case '|':
            return 3;
        case '(':
            return 5;
    }
}

