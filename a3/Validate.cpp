/*
 * Programmers: An Le
 * Username: masc0749
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Validate.cpp
 */

#include "Validate.h"

// -------------------Validate Digit---------------------
struct charDigit {
    char charDigitZeroToNine;
};

const struct charDigit charDigitTable[] = {
    { '0' },   { '1' },
    { '2' },   { '3' },
    { '4' },   { '5' },
    { '6' },   { '7' },
    { '8' },   { '9' },
};

bool Validate::validateDigit (char digit){
    for(int i = 0; i < 10; i++){
        if(charDigitTable[i].charDigitZeroToNine == digit)
            return true;
    }
    return false;
}

// -------------------Validate Operators---------------------
struct operators {
    char charOperators;
};

const struct operators charOperatorsTable [] = {
    { '+' },   { '-' },
    { '*' },   { '/' },
    { '%' },
};

bool Validate::validateOperators (char operators){
    for(int i = 0; i < 5; i++){
        if(charOperatorsTable[i].charOperators == operators)
            return true;
    }
    return false;
}

// -------------------Validate Character---------------------
struct characters {
    char character_aToZ;
};

const struct characters characterTable [] = {
    { 'a' },   { 'b' },    { 'c' },    { 'd' },
    { 'e' },   { 'f' },    { 'g' },    { 'h' },
    { 'i' },   { 'j' },    { 'k' },    { 'l' },
    { 'm' },   { 'n' },    { 'o' },    { 'p' },
    { 'q' },   { 'r' },    { 's' },    { 't' },
    { 'u' },   { 'v' },    { 'w' },    { 'x' },
    { 'y' },   { 'z' },    { 'A' },    { 'B' },
    { 'C' },   { 'D' },    { 'E' },    { 'F' },
    { 'G' },   { 'H' },    { 'I' },    { 'J' },
    { 'K' },   { 'L' },    { 'M' },    { 'N' },
    { 'O' },   { 'P' },    { 'Q' },    { 'R' },
    { 'S' },   { 'T' },    { 'U' },    { 'V' },
    { 'W' },   { 'X' },    { 'Y' },    { 'Z' },
};

bool Validate::validateCharacter(char character) {
    for(int i = 0; i < 52; i++) {
        if(characterTable[i].character_aToZ == character)
            return true;
    }
    return false;
}

// -------------------Validate ID---------------------
bool Validate::validateID (string token) {
    // Check if the first char of token is letter
    if(validateCharacter(token[0])) {
        // Check the rest char of token if they are either letter or number
        for(int i = 1; i < token.length(); i++) {
            if(validateCharacter(token[i]))
                continue;
            else if(validateDigit(token[i]))
                continue;
            else {
                return false;
            }
        }
        return true;
    }
    return false;
}

// -------------------Validate Expression---------------------
vector<string> Validate::validateExp(vector<string> token){
    vector<string> result(2);
    stringstream ss;
    Validate *validate = new Validate();
    // Check if the first token is ID
    if (token[0] != " " && validate->validateID(token[0])) {
        // Check the next token is Op
        if (token[1].length() == 1 && validate->validateOperators(token[1][0])) {
            // Check if the last token is ID
            if (validate->validateID(token[token.size()-1])) {
                for (int i = 2; i < token.size()-1; i++) {
                    if (!(validate->validateID(token[i]))) {
                        result[0] = "0";
                        ss << "The token \"" << token[i] << "\" is not a valid ID.";
                        result[1] = ss.str();
                        return result;
                    }
                    i = i + 1;
                    if (!(validate->validateOperators(token[i][0]))) {
                        result[0] = "0";
                        ss << "The token \"" << token[i] << "\" is not a valid Operator.";
                        result[1] = ss.str();
                        return result;
                    }
                }
                result[0] = "1";
                result[1] = " ";
                return result;
            }
            result[0] = "0";
            ss << "The token \"" << token[token.size()-1] << "\" is not a valid ID.";
            result[1] = ss.str();
            return result;
        }
        result[0] = "0";
        ss << "The token \"" << token[1] << "\" is not a valid Operator.";
        result[1] = ss.str();
        return result;
    }
    result[0] = "0";
    ss << "The token \"" << token[0] << "\" is not a valid ID.";
    result[1] = ss.str();
    return result;
}

// -------------------Validate Assignment---------------------
vector<string> Validate::validateAssg(vector<string> token){
    vector<string> result(2);
    stringstream ss;
    Validate *validate = new Validate();
    // Check the first token is ID
    if (validate->validateID(token[0])) {
        // Check the second token is = sign
        if (token[1] == "=") {
            // Check the last token is ;
            if (token[token.size() - 1][0] == ';') {
                vector<string> theRest;
                for (int i = 2; i < token.size()-1; i++) {
                    theRest.push_back(token[i]);
                }
                return validateExp(theRest);
            }
            result[0] = "0";
            ss << "The last token \"" << token[token.size() - 1] << "\" is not a semi colon.";
            result[1] = ss.str();
            return result;
        }
        result[0] = "0";
        ss << "The second token \"" << token[1] << "\" is not an equal sign.";
        result[1] = ss.str();
        return result;
    }
    result[0] = "0";
    ss << "The first token \"" << token[0] << "\" is not a valid ID.";
    result[1] = ss.str();
    return result;
}