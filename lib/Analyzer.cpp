//
// Created by Nathan on 14/12/2017.
//

#include "Analyzer.h"
#include <iostream>
#include "../re/RE.h"

using namespace::std;

Analyzer::Analyzer(ODFA &odfa, string code) {
    this->odfa = odfa;
    this->code = code;
}

void Analyzer::run() {
//    odfa.printODFA();
//    cout<<code<<endl;
    OSet currentOSet = odfa.headSet;
    for(auto edge: code){
        int findFlag = 0;
        for(auto triplet: odfa.oSetTriplets){
            if(triplet.head.set == currentOSet.set && triplet.edge == char2string(edge)){
                currentOSet = triplet.tail;
                findFlag = 1;
                break;
            }
        }
        if(!findFlag){
            cout<<"error occur: 找不到边"<<endl;
        }else{
            for(auto set: currentOSet.set){
                for(auto state: set){
                    cout<<state<<",";
                }
                cout<<endl;
            }
            cout<<currentOSet.tokenName<<endl;
            cout<<"@@@@@@@@@@@@@@@@@@@"<<endl;
        }
    }
    Token token = Token(code,currentOSet.tokenName,++tokenMap[currentOSet.tokenName]);
    token.printToken();
//    for(auto set: currentOSet.set){
//        for(auto state: set){
//            cout<<state<<",";
//        }
//        cout<<endl;
//    }
}