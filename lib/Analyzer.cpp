//
// Created by Nathan on 14/12/2017.
//

#include "Analyzer.h"
#include <iostream>
#include "../re/RE.h"

using namespace::std;

Analyzer::Analyzer(ODFA &odfa) {
    this->odfa = odfa;
//    set<set<int>> emptySet;
//    OSet emptyOSet(emptySet,0);
//    banTriplet = OSetTriplet(emptyOSet,"",emptyOSet);
}

void Analyzer::run(string code) {
    initReserverToken();
    OSet currentOSet = odfa.headSet;
    for(int i=0; i<code.size(); i++){
        int findFlag = 0;
        // push进word
        if(!isInEmptyTable(code[i])){
            word.push_back(code[i]);
        }
        for(auto triplet: odfa.oSetTriplets){
            if(triplet.head.set == currentOSet.set && triplet.edge == char2string(code[i])){
                currentOSet = triplet.tail;
                findFlag = 1;
                break;
            }
        }
        if(findFlag){
            // 为终态
            if(currentOSet.tokenName != "") {
//                cout << "tokenName " << currentOSet.tokenName << endl;
                if (currentOSet.tokenName == "id") {
                    // 判断是否是保留字
                    if (isReserved()) {
                        isReserve = true;
                    } else if (isInDigitTable(code[i + 1]) || isInCapitalLetterTable(code[i + 1]) ||
                               isInLetterTable(code[i + 1])) {
                        // continue
                    } else {
                        string lexme = pop_word();
                        if(isTokenExsits(lexme)){
                            //pass
                            pop_word();
                        }else{
                            Token token = Token(lexme, currentOSet.tokenName, ++tokenMap[currentOSet.tokenName]);
//                            token.printToken();
                            tokens.push_back(token);
                        }
                        currentOSet = odfa.headSet;
                    }
                } else if (currentOSet.tokenName == "ws") {
                    // empty
                    currentOSet = odfa.headSet;
                }
                else if(currentOSet.tokenName == "digits"){
                    if (isInDigitTable(code[i + 1])){
                        // continue
                    } else {
                        string lexme = pop_word();
                        if(isTokenExsits(lexme)){
                            pop_word();
                        }else{
                            Token token = Token(lexme, currentOSet.tokenName, ++tokenMap[currentOSet.tokenName]);
//                            token.printToken();
                            tokens.push_back(token);
                        }
                        currentOSet = odfa.headSet;
                    }
                }
            else {
                    string lexme = pop_word();
                    if(isTokenExsits(lexme)){
                        pop_word();
                    }else{
                        Token token = Token(lexme, currentOSet.tokenName, -1);
                        tokens.push_back(token);
                    }
                    currentOSet = odfa.headSet;
                }
                // 保留字

                if (isReserve) {
                    isReserve = false;
                    string lexme = pop_word();
                    if(isTokenExsits(lexme)){
                        pop_word();
                    }else{
                        Token token = Token(lexme, currentOSet.tokenName, -1);
                        tokens.push_back(token);
                    }
                    currentOSet = odfa.headSet;
                }
            }
        }else{
            cout<<"error occur: Unidentified words"<<endl;
            int emptyFlag = 0;
            int continueFlag = 0;
            for(;i<code.size(); i++){
                if(code[i] == ' '){
                    emptyFlag = 1;
                }
                if(emptyFlag && code[i] != ' '){
                    continueFlag = 1;
                }
                if(continueFlag){
                    break;
                }
            }
            currentOSet = odfa.headSet;
            pop_word();
        }
    }
}

bool Analyzer::isReserved() {
    for(auto tokenName: reservedTokenMap){
        string lexme = current_word();
        if (lexme == tokenName) {
            reserveTokenName = lexme;
            return true;
        }
    }
    return false;
}

string Analyzer::current_word() {
    string lexme;
    for(auto letter: word){
        lexme.insert(lexme.size(),char2string(letter));
    }
    return lexme;
}

string Analyzer::pop_word() {
    string lexme;
    for(auto letter: word){
        lexme.insert(lexme.size(),char2string(letter));
    }
    word.clear();
    return lexme;
}

bool Analyzer::isTokenExsits(string token) {
    for(auto _token: tokens){
        if(token == _token.lexme){
            return true;
        }
    }
    return false;
}

void Analyzer::printTokens() {
    for(auto token: tokens){
        token.printToken();
    }
}
