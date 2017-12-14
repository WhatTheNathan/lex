//
// Created by Nathan on 14/12/2017.
//

#include "NFA.h"
#include <stack>

using namespace::std;

NFA::NFA(std::string re) {
    adddot(re);
}

string NFA::adddot(std::string re) {
    for(int i=0; i<re.size(); i++){
        if( (re[i] == '*') && (re[i+1] != nullptr)) {
            re.insert(i+1,".");
        }
        if( re[i] == ')' && (re[i+1] != nullptr)) {
            re.insert(i+1,".");
        }
    }
}

// 运算符优先级高的入栈，比栈中低，则栈中运算符出栈
string NFA::infix2postfix(string re) {

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

