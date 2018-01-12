//
// Created by Nathan on 14/12/2017.
//

#include "NFA.h"
#include <iostream>
#include "../re/RE.h"

using namespace::std;

int NFA::stateCount = 0;
stack<NFA> subnfa_stack; // 子NFA的栈

NFA::NFA(std::string re, bool isLetter) {
    if(isLetter){
        headState = ++stateCount;
        tailState = ++stateCount;
        Triplet triple = Triplet(headState,re,tailState);
        triplets.push_back(triple);
    }else {
        re = batchprocess(re);
        preprocess(re);
        adddot(re);
        string postfixRE = infix2postfix(re);
        convert2nfa(postfixRE);

//        cout<<"re: "<<re<<endl;
//        cout<<"postfixRE: "<<postfixRE<<endl;
//        printNFA();
    }
}

string NFA::batchprocess(string re) {
    std::string expression = "";
    int count = 0;
    while(re[count] != '-'){
        this->tokenName.insert(count,char2string(re[count]));
        count++;
    }
    count += 2;
    int index = 0;
    while(count < re.length()){
        expression.insert(index,char2string(re[count]));
        index++;
        count++;
    }
    tokenMap[tokenName] = 0;
    return expression;
}

void NFA::preprocess(std::string &re) {
    for(int i=0; i<re.size(); i++){
        if(re[i] == '['){
            int position = i;
            if(isInDigitTable(re[i+1])){
                firstLetter = re[++i];
                i++;
                endLetter = re[++i];
                re.erase(re.begin()+position,re.begin()+position+5);
                re.insert(position++, "(");
                for(int i=0; i<digitTable.size(); i++){
                    re.insert(position++,char2string(digitTable[i]));
                    if(i != digitTable.size()-1) {
                        re.insert(position++, "|");
                    }
                }
                re.insert(position++, ")");
            }else if(isInCapitalLetterTable(re[i+1])){
                firstLetter = re[++i];
                i++;
                endLetter = re[++i];
            }else if(isInLetterTable(re[i+1])){
                firstLetter = re[++i];
                i++;
                endLetter = re[++i];
            }else {
                cout<<"error occur: invilid '['"<<endl;
            }
        }
    }
}

void NFA::adddot(std::string& re) {
    for(int i=0; i<re.size(); i++){
        if( ( (re[i] == ')') || (re[i] == '*') || (re[i] == '+')) && ((i+1) != re.size() && re[i+1] != '*' && re[i+1] != '+')) {
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
        if(re[i] == '(' || re[i] == '*' || re[i] == '|' || re[i] == '.' || re[i] == '+'){
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
            edges.insert(char2string(re[i]));
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
        if(isInDigitTable(re[i]) || isInCapitalLetterTable(re[i]) || isInLetterTable(re[i])){
            NFA subnfa = NFA(char2string(re[i]),true);
            subnfa_stack.push(subnfa);
        }
        else if(re[i] == '*'){
            subnfa_stack.top().mutiply();
        }
        else if(re[i] == '+'){
            subnfa_stack.top().add();
        }
        else if(re[i] == '|'){
            NFA sub_right_nfa = subnfa_stack.top();
            subnfa_stack.pop();
            subnfa_stack.top().orr(sub_right_nfa);
        }
        else if(re[i] == '.'){
            NFA sub_right_nfa = subnfa_stack.top();
            subnfa_stack.pop();
            subnfa_stack.top().connect(sub_right_nfa);
        }
    }
    NFA finalNFA = subnfa_stack.top();
    triplets = finalNFA.triplets;
    headState = finalNFA.headState;
    tailState = finalNFA.tailState;
    // 加入terminal-token表中
    terminalVec.push_back(tailState);
    terminalMap[tailState] = tokenName;
    subnfa_stack.pop();

//    finalNFA.printNFA();
}

void NFA::mutiply() {
    triplets.push_back(Triplet(tailState,"e",headState));
    int pre_headState = headState;
    int pre_tailState = tailState;

    headState = ++stateCount;
    tailState = ++stateCount;
    triplets.push_back(Triplet(headState,"e",pre_headState));
    triplets.push_back(Triplet(headState,"e",tailState));
    triplets.push_back(Triplet(pre_tailState,"e",tailState));
}

void NFA::add() {
    triplets.push_back(Triplet(tailState,"e",headState));
    int pre_headState = headState;
    int pre_tailState = tailState;

    headState = ++stateCount;
    tailState = ++stateCount;
    triplets.push_back(Triplet(headState,"e",pre_headState));
    triplets.push_back(Triplet(pre_tailState,"e",tailState));
}

void NFA::orr(NFA nfa) {
    triplets.insert(triplets.end(),nfa.triplets.begin(),nfa.triplets.end());
    int preself_headState = headState;
    int preself_tailState = tailState;

    headState = ++stateCount;
    tailState = ++stateCount;

    triplets.push_back(Triplet(headState,"e",preself_headState));
    triplets.push_back(Triplet(headState,"e",nfa.headState));

    triplets.push_back(Triplet(nfa.tailState,"e",tailState));
    triplets.push_back(Triplet(preself_tailState,"e",tailState));
}

void NFA::connect(NFA nfa) {
    triplets.insert(triplets.end(),nfa.triplets.begin(),nfa.triplets.end());
    triplets.push_back(Triplet(tailState,"e",nfa.headState));
    tailState = nfa.tailState;
}

int NFA::isp(char op) {
    switch(op){
        case '*':
            return 4;
        case '+':
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
        case '+':
            return 4;
        case '.':
            return 2;
        case '|':
            return 3;
        case '(':
            return 5;
    }
}

void NFA::merge(vector<NFA> nfas) {
    int leftHeadState = headState;
    headState = ++stateCount;
    triplets.push_back(Triplet(headState,"e",leftHeadState));

    for(auto nfa: nfas){
        // 合并edges
        for(auto edge: nfa.edges){
            edges.insert(edge);
        }
        triplets.insert(triplets.end(),nfa.triplets.begin(),nfa.triplets.end());
        int rightHeadState = nfa.headState;
        triplets.push_back(Triplet(headState,"e",rightHeadState));

        map<int,std::string>::iterator iter;
        for( iter=nfa.terminalMap.begin(); iter!=nfa.terminalMap.end(); iter++)
        {
            this->terminalMap[iter->first] = iter->second;
            this->terminalVec.push_back(iter->first);
        }
    }
}

void NFA::printNFA() {
    cout<<"headState "<<headState<<endl;
    cout<<"tailState "<<tailState<<endl;
    for(auto triplet : triplets){
        cout<<triplet.head<<"-"<<triplet.edge<<"-"<<triplet.tail<<endl;
    }
    cout<<"terminal-token table"<<endl;
    map<int,std::string>::iterator it;
    for( it=this->terminalMap.begin(); it!=this->terminalMap.end(); it++)
    {
        cout<<"("<<it->first<<","<<it->second<<")"<<endl;
    }
}

