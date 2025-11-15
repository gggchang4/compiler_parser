#include "parser.h"
#include <iostream>
#include <sstream>

Parser::Parser(const std::string& input) : lexer(input), hasMain(false) {
    current = lexer.nextToken();
    if (current.type == UNKNOWN) {
        error("Lexical error");
    }
}

void Parser::advance() {
    current = lexer.nextToken();
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    return current.type == type;
}

void Parser::error(const std::string& msg) {
    int line = current.line;
    for (const auto& err : errors) {
        if (err.line == line) {
            return;
        }
    }
    errors.push_back(ErrorInfo(line, msg));
}

void Parser::errorExpected(const std::string& expected) {
    std::string msg = "Expected " + expected;
    error(msg);
}

void Parser::parseCompUnit() {
    if (check(END_OF_FILE)) {
        error("Empty program");
        return;
    }
    
    while (!check(END_OF_FILE)) {
        int errorCountBefore = errors.size();
        int tokenIndexBefore = current.index;
        parseFuncDef();
        int errorCountAfter = errors.size();
        int tokenIndexAfter = current.index;
        
        if (errorCountAfter > errorCountBefore) {
            if (tokenIndexBefore == tokenIndexAfter) {
                break;
            }
            if (check(LEFT_BRACE)) {
                break;
            }
            while (!check(END_OF_FILE) && !check(INT) && !check(VOID)) {
                advance();
            }
        } else if (tokenIndexBefore == tokenIndexAfter && !check(END_OF_FILE)) {
            advance();
        }
        
        if (check(END_OF_FILE)) {
            break;
        }
    }
    
    if (!hasMain) {
        error("Missing main function");
    }
}

void Parser::parseFuncDef() {
    if (!check(INT) && !check(VOID)) {
        errorExpected("int or void");
        return;
    }
    advance();
    
    if (!check(IDENTIFIER)) {
        errorExpected("function name");
        return;
    }
    
    std::string funcName = current.value;
    advance();
    
    if (funcName == "main") {
        hasMain = true;
    }
    
    if (functionNames.find(funcName) != functionNames.end()) {
        error("Duplicate function name");
    } else {
        functionNames.insert(funcName);
    }
    
    if (!match(LEFT_PAREN)) {
        errorExpected("(");
        if (check(RIGHT_PAREN)) {
            advance();
        }
        return;
    }
    
    if (check(INT)) {
        int paramErrorBefore = errors.size();
        parseParam();
        if (errors.size() > paramErrorBefore) {
            // If first parameter has error, skip to closing paren without parsing more parameters
            while (!check(RIGHT_PAREN) && !check(END_OF_FILE) && !check(LEFT_BRACE)) {
                advance();
            }
        } else {
            while (match(COMMA)) {
                if (check(RIGHT_PAREN)) {
                    break;
                }
                int paramErrorBefore2 = errors.size();
                parseParam();
                // If a parameter after comma has error, stop parsing more parameters
                if (errors.size() > paramErrorBefore2) {
                    break;
                }
            }
        }
    } else if (check(COMMA)) {
        // Handle case where first parameter is missing (comma after opening paren)
        errorExpected("int");
        // Skip to closing paren
        while (!check(RIGHT_PAREN) && !check(END_OF_FILE) && !check(LEFT_BRACE)) {
            advance();
        }
    }
    
    if (!match(RIGHT_PAREN)) {
        errorExpected(")");
        return;
    }
    
    parseBlock();
}

void Parser::parseParam() {
    if (!match(INT)) {
        errorExpected("int");
        return;
    }
    
    if (!match(IDENTIFIER)) {
        errorExpected("parameter name");
        return;
    }
}

void Parser::parseStmt() {
    if (check(LEFT_BRACE)) {
        parseBlock();
    } else if (match(SEMICOLON)) {
        return;
    } else if (check(INT)) {
        advance();
        if (!match(IDENTIFIER)) {
            errorExpected("variable name");
            return;
        }
        if (!match(ASSIGN)) {
            errorExpected("=");
            return;
        }
        parseExpr();
        if (!match(SEMICOLON)) {
            errorExpected(";");
        }
    } else if (check(IDENTIFIER)) {
        Token idToken = current;
        advance();
        if (check(ASSIGN)) {
            advance();
            parseExpr();
            if (!match(SEMICOLON)) {
                errorExpected(";");
            }
        } else if (check(LEFT_PAREN)) {
            advance();
            if (!check(RIGHT_PAREN)) {
                if (check(COMMA)) {
                    error("Missing argument");
                } else {
                    parseExpr();
                    while (match(COMMA)) {
                        if (check(RIGHT_PAREN) || check(SEMICOLON) || 
                            check(END_OF_FILE)) {
                            error("Missing argument");
                            break;
                        }
                        parseExpr();
                    }
                }
            }
            if (!match(RIGHT_PAREN)) {
                errorExpected(")");
            }
            if (!match(SEMICOLON)) {
                errorExpected(";");
            }
        } else {
            error("Invalid statement");
        }
    } else if (check(IF)) {
        advance();
        if (!match(LEFT_PAREN)) {
            errorExpected("(");
            return;
        }
        parseExpr();
        if (!match(RIGHT_PAREN)) {
            errorExpected(")");
            return;
        }
        parseStmt();
        if (match(ELSE)) {
            parseStmt();
        }
    } else if (check(WHILE)) {
        advance();
        if (!match(LEFT_PAREN)) {
            errorExpected("(");
            return;
        }
        parseExpr();
        if (!match(RIGHT_PAREN)) {
            errorExpected(")");
            return;
        }
        parseStmt();
    } else if (check(BREAK)) {
        advance();
        if (!match(SEMICOLON)) {
            errorExpected(";");
        }
    } else if (check(CONTINUE)) {
        advance();
        if (!match(SEMICOLON)) {
            errorExpected(";");
        }
    } else if (check(RETURN)) {
        advance();
        parseExpr();
        if (!match(SEMICOLON)) {
            errorExpected(";");
        }
    } else if (check(ELSE)) {
        // Skip else that appears without a matching if (error recovery)
        advance();
    } else {
        parseExpr();
        if (!match(SEMICOLON)) {
            errorExpected(";");
        }
    }
}

void Parser::parseBlock() {
    if (!match(LEFT_BRACE)) {
        errorExpected("{");
        return;
    }
    
    while (!check(RIGHT_BRACE) && !check(END_OF_FILE)) {
        int beforeIndex = current.index;
        parseStmt();
        int afterIndex = current.index;
        
        if (beforeIndex == afterIndex && !check(RIGHT_BRACE) && !check(END_OF_FILE)) {
            advance();
        }
        
        if (errors.size() > 0 && check(END_OF_FILE)) {
            break;
        }
    }
    
    if (!match(RIGHT_BRACE)) {
        errorExpected("}");
    }
}

void Parser::parseExpr() {
    parseLOrExpr();
}

void Parser::parseLOrExpr() {
    parseLAndExpr();
    while (match(OR)) {
        parseLAndExpr();
    }
}

void Parser::parseLAndExpr() {
    parseRelExpr();
    while (match(AND)) {
        parseRelExpr();
    }
}

void Parser::parseRelExpr() {
    parseAddExpr();
    while (check(LESS) || check(GREATER) || check(LESS_EQUAL) || 
           check(GREATER_EQUAL) || check(EQUAL) || check(NOT_EQUAL)) {
        advance();
        parseAddExpr();
    }
}

void Parser::parseAddExpr() {
    parseMulExpr();
    while (check(PLUS) || check(MINUS)) {
        advance();
        if (check(SEMICOLON) || check(RIGHT_PAREN) || check(RIGHT_BRACE) || 
            check(COMMA) || check(END_OF_FILE)) {
            error("Missing operand");
            return;
        }
        parseMulExpr();
    }
}

void Parser::parseMulExpr() {
    parseUnaryExpr();
    while (check(MULTIPLY) || check(DIVIDE) || check(MODULO)) {
        advance();
        if (check(SEMICOLON) || check(RIGHT_PAREN) || check(RIGHT_BRACE) || 
            check(COMMA) || check(END_OF_FILE)) {
            error("Missing operand");
            return;
        }
        parseUnaryExpr();
    }
}

void Parser::parseUnaryExpr() {
    if (check(PLUS) || check(MINUS) || check(NOT)) {
        advance();
        if (check(SEMICOLON) || check(RIGHT_PAREN) || check(RIGHT_BRACE) || 
            check(COMMA) || check(END_OF_FILE)) {
            error("Missing operand");
            return;
        }
        parseUnaryExpr();
    } else {
        parsePrimaryExpr();
    }
}

void Parser::parsePrimaryExpr() {
    if (check(IDENTIFIER)) {
        Token idToken = current;
        advance();
        if (check(LEFT_PAREN)) {
            advance();
            if (!check(RIGHT_PAREN)) {
                if (check(COMMA)) {
                    error("Missing argument");
                } else {
                    parseExpr();
                    while (match(COMMA)) {
                        if (check(RIGHT_PAREN) || check(SEMICOLON) || 
                            check(END_OF_FILE)) {
                            error("Missing argument");
                            break;
                        }
                        parseExpr();
                    }
                }
            }
            if (!match(RIGHT_PAREN)) {
                errorExpected(")");
            }
        }
    } else if (match(INTCONST)) {
        return;
    } else if (match(LEFT_PAREN)) {
        parseExpr();
        if (!match(RIGHT_PAREN)) {
            errorExpected(")");
        }
    } else {
        errorExpected("expression");
    }
}

bool Parser::parse() {
    parseCompUnit();
    return errors.empty();
}

void Parser::printErrors() {
    if (errors.empty()) {
        std::cout << "accept" << std::endl;
    } else {
        std::cout << "reject" << std::endl;
        std::set<int> seenLines;
        for (const auto& err : errors) {
            if (seenLines.find(err.line) == seenLines.end()) {
                std::cout << err.line << std::endl;
                seenLines.insert(err.line);
            }
        }
    }
}

