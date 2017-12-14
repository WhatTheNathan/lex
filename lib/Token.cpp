//
// Created by Nathan on 14/12/2017.
//
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