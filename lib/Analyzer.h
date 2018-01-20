//
// Created by Nathan on 14/12/2017.
//

#ifndef N_LEXER_ANALYZER_H
#define N_LEXER_ANALYZER_H


#include "ODFA.h"
#include "Token.h"

class Analyzer {
public:
    Analyzer(ODFA &odfa);
    void run(std::string code);
    void printTokens();
private:
    std::vector<Token> tokens;
    std::vector<char> word;
    ODFA odfa;

    bool isReserve;
    std::string reserveTokenName;

    bool isReserved();               //识别是否为保留字
    std::string current_word();      //目前word
    std::string pop_word();          //弹出word
    bool isTokenExsits(std::string token);
};


#endif //N_LEXER_ANALYZER_H