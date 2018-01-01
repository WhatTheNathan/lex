//
// Created by Nathan on 01/01/2018.
//

#ifndef N_LEXER_RE_H
#define N_LEXER_RE_H

#include "string"
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

// 先构造一个函数将所有的表达式文法推断了
// edge要换成string
// 加入运算符+
// 先把[0-9]+例子构造完

static std::vector<char> digitTable = {'0','1','2','3','4','5','6','7','8','9'};
static std::vector<char> capitalLetterTable = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
                                         'W','X','Y','Z'};
static std::vector<char> letterTable = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
                                  'y','z'};

static std::string char2string(char _char){
    std::stringstream stream;
    stream << _char;
    std::string str = stream.str();
    return str;
}

static bool isInDigitTable(char digit){
    for(int i=0; i<digitTable.size(); i++){
        if(digit == digitTable[i]){
            return true;
            break;
        }
    }
    return false;
}

static bool isInCapitalLetterTable(char letter){
    for(int i=0; i<capitalLetterTable.size(); i++){
        if(letter == capitalLetterTable[i]){
            return true;
            break;
        }
    }
    return false;
}

static bool isInLetterTable(char letter){
    for(int i=0; i<letterTable.size(); i++){
        if(letter == letterTable[i]){
            return true;
            break;
        }
    }
    return false;
}

static std::map<std::string,std::string> map;
static void addRE(std::string re){
    std::string tokenName = "";
    std::string expression = "";
    int count = 0;
    while(re[count] != '-'){
        tokenName.insert(count,char2string(re[count]));
        count++;
    }
    count += 2;
    int index = 0;
    while(count < re.length()){
        expression.insert(index,char2string(re[count]));
        index++;
        count++;
    }
    map[tokenName] = expression;
}

static std::string digit = "digit->[0-9]";
static std::string digits = "digits->digit+";





#endif //N_LEXER_RE_H
