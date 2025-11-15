#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <vector>
#include <string>
#include <set>

struct ErrorInfo {
    int line;
    std::string message;
    
    ErrorInfo(int l, const std::string& m) : line(l), message(m) {}
};

class Parser {
private:
    Lexer lexer;
    Token current;
    std::vector<ErrorInfo> errors;
    bool hasMain;
    std::set<std::string> functionNames;
    
    void advance();
    bool match(TokenType type);
    bool check(TokenType type);
    void error(const std::string& msg);
    void errorExpected(const std::string& expected);
    
    void parseCompUnit();
    void parseFuncDef();
    void parseParam();
    void parseStmt();
    void parseBlock();
    void parseExpr();
    void parseLOrExpr();
    void parseLAndExpr();
    void parseRelExpr();
    void parseAddExpr();
    void parseMulExpr();
    void parseUnaryExpr();
    void parsePrimaryExpr();
    
public:
    Parser(const std::string& input);
    bool parse();
    void printErrors();
};

#endif

