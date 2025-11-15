#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

enum TokenType {
    INT, VOID, IF, ELSE, WHILE, BREAK, CONTINUE, RETURN,
    IDENTIFIER, INTCONST,
    PLUS, MINUS, MULTIPLY, DIVIDE, MODULO,
    ASSIGN, EQUAL, NOT_EQUAL,
    LESS, LESS_EQUAL, GREATER, GREATER_EQUAL,
    AND, OR, NOT,
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    SEMICOLON, COMMA,
    END_OF_FILE, UNKNOWN
};

struct Token {
    TokenType type;
    string value;
    int index;
    int line;
    
    Token() : type(END_OF_FILE), value(""), index(0), line(1) {}
    Token(TokenType t, const string& v, int idx, int l = 1) : type(t), value(v), index(idx), line(l) {}
};

class Lexer {
private:
    string input;
    int pos;
    int tokenIndex;
    int line;
    map<string, TokenType> keywordMap;
    
    void initKeywords();
    char getChar();
    char peek();
    void next();
    void skipSpace();
    void skipComments();
    Token readNumber();
    Token readId();
    Token readOp();
    string typeToStr(TokenType t);
    
public:
    Lexer(string s);
    Token nextToken();
    vector<Token> getAllTokens();
    void output();
};

#endif
