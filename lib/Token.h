//
// Created by Nathan on 01/01/2018.
//

#ifndef N_LEXER_TOKEN_H
#define N_LEXER_TOKEN_H


#include <string>

class Token {
public:
    std::string lexme;
    std::string tokenName;
    int attrValue;

    Token(std::string _lexme , std::string _tokenName, int _attrValue){
        lexme = _lexme;
        tokenName = _tokenName;
        attrValue = _attrValue;
    }

    void printToken();
};


#endif //N_LEXER_TOKEN_H
