//
// Created by Nathan on 14/12/2017.
//

#ifndef N_LEXER_ANALYZER_H
#define N_LEXER_ANALYZER_H


#include "ODFA.h"
#include "Token.h"

class Analyzer {
public:
    Analyzer(ODFA &odfa,std::string code);
    void run();
private:
    std::vector<Token> tokens;
    std::vector<char> word;
    ODFA odfa;
    std::string code;

    bool isReserved(OSet oSet);      //识别是否为保留字
    std::string pop_word();          //弹出word

    OSetTriplet banTriplet;                 //ban掉保留字的path
    bool isReserve;
    std::string reserveTokenName;
};


#endif //N_LEXER_ANALYZER_H