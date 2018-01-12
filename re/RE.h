//
// Created by Nathan on 01/01/2018.
//

#include "string"
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

static std::vector<char> digitTable = {'0','1','2','3','4','5','6','7','8','9'};
static std::vector<char> capitalLetterTable = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
                                         'W','X','Y','Z'};
static std::vector<char> letterTable = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
                                  'y','z'};
static std::vector<char> operatorTable = {'<','>','=','!'};

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

/// MARK -
static std::map<std::string,int> tokenMap;

static std::string re = "test->(a*b)*(a|b)";
static std::string digit = "digit->[0-9]";
static std::string digits = "digits->[0-9]+";

static std::string _if = "if->if";
static std::string _then = "then->then";
static std::string _else = "else->else";
static std::string relop = "relop-><|>|<=|>=|=|!=";
