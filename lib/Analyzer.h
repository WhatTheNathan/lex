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
    ODFA odfa;
    std::string code;
};


#endif //N_LEXER_ANALYZER_H
