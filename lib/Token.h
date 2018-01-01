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
    std::string attrValue;

    Token(std::string _lexme , std::string _tokenName, std::string _attrValue){
        lexme = _lexme;
        tokenName = _tokenName;
        attrValue = _attrValue;
    }
};


#endif //N_LEXER_TOKEN_H
