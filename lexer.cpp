#include "lexer.h"
#include <cctype>
#include <sstream>

Lexer::Lexer(string s) {
    input = s;
    pos = 0;
    tokenIndex = 0;
    line = 1;
    initKeywords();
}

void Lexer::initKeywords() {
    keywordMap["int"] = INT;
    keywordMap["void"] = VOID;
    keywordMap["if"] = IF;
    keywordMap["else"] = ELSE;
    keywordMap["while"] = WHILE;
    keywordMap["break"] = BREAK;
    keywordMap["continue"] = CONTINUE;
    keywordMap["return"] = RETURN;
}

char Lexer::getChar() {
    if (pos >= (int)input.length()) {
        return '\0';
    }
    return input[pos];
}

char Lexer::peek() {
    if (pos + 1 >= (int)input.length()) {
        return '\0';
    }
    return input[pos + 1];
}

void Lexer::next() {
    if (pos < (int)input.length()) {
        if (input[pos] == '\n') {
            line++;
        }
        pos++;
    }
}

void Lexer::skipSpace() {
    while (pos < (int)input.length()) {
        char c = getChar();
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v') {
            next();
        } else {
            break;
        }
    }
}

void Lexer::skipComments() {
    char c1 = getChar();
    char c2 = peek();
    
    if (c1 == '/' && c2 == '/') {
        // Skip the two slashes
        next();
        next();
        // Skip until newline or end of input
        while (pos < (int)input.length() && getChar() != '\n') {
            next();
        }
        // If we found a newline, skip it (let skipSpace() handle it in next iteration)
        // If we didn't find a newline, we've reached end of input
    } else if (c1 == '/' && c2 == '*') {
        next();
        next();
        while (pos < (int)input.length()) {
            if (getChar() == '*' && peek() == '/') {
                next();
                next();
                break;
            }
            next();
        }
    }
}

Token Lexer::readNumber() {
    string num = "";
    int startLine = line;
    
    if (pos >= (int)input.length() || getChar() < '0' || getChar() > '9') {
        return Token(UNKNOWN, "", tokenIndex++, startLine);
    }
    
    char firstDigit = getChar();
    num += firstDigit;
    next();
    
    if (firstDigit == '0') {
        Token t(INTCONST, num, tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    
    while (pos < (int)input.length()) {
        char c = getChar();
        if (c >= '0' && c <= '9') {
            num += c;
            next();
        } else {
            break;
        }
    }
    
    Token t(INTCONST, num, tokenIndex, startLine);
    tokenIndex++;
    return t;
}

Token Lexer::readId() {
    string id = "";
    int startLine = line;
    
    while (pos < (int)input.length()) {
        char c = getChar();
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9') || c == '_') {
            id += c;
            next();
        } else {
            break;
        }
    }
    
    if (keywordMap.find(id) != keywordMap.end()) {
        Token t(keywordMap[id], id, tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    
    Token t(IDENTIFIER, id, tokenIndex, startLine);
    tokenIndex++;
    return t;
}

Token Lexer::readOp() {
    char c = getChar();
    int startLine = line;
    Token t;
    
    if (c == '+') {
        next();
        t = Token(PLUS, "+", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '-') {
        next();
        t = Token(MINUS, "-", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '*') {
        next();
        t = Token(MULTIPLY, "*", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '/') {
        next();
        t = Token(DIVIDE, "/", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '%') {
        next();
        t = Token(MODULO, "%", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '=') {
        next();
        if (getChar() == '=') {
            next();
            t = Token(EQUAL, "==", tokenIndex, startLine);
            tokenIndex++;
            return t;
        }
        t = Token(ASSIGN, "=", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '!') {
        next();
        if (getChar() == '=') {
            next();
            t = Token(NOT_EQUAL, "!=", tokenIndex, startLine);
            tokenIndex++;
            return t;
        }
        t = Token(NOT, "!", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '<') {
        next();
        if (getChar() == '=') {
            next();
            t = Token(LESS_EQUAL, "<=", tokenIndex, startLine);
            tokenIndex++;
            return t;
        }
        t = Token(LESS, "<", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '>') {
        next();
        if (getChar() == '=') {
            next();
            t = Token(GREATER_EQUAL, ">=", tokenIndex, startLine);
            tokenIndex++;
            return t;
        }
        t = Token(GREATER, ">", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '&') {
        next();
        if (getChar() == '&') {
            next();
            t = Token(AND, "&&", tokenIndex, startLine);
            tokenIndex++;
            return t;
        }
        t = Token(UNKNOWN, "&", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '|') {
        next();
        if (getChar() == '|') {
            next();
            t = Token(OR, "||", tokenIndex, startLine);
            tokenIndex++;
            return t;
        }
        t = Token(UNKNOWN, "|", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '(') {
        next();
        t = Token(LEFT_PAREN, "(", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == ')') {
        next();
        t = Token(RIGHT_PAREN, ")", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '{') {
        next();
        t = Token(LEFT_BRACE, "{", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == '}') {
        next();
        t = Token(RIGHT_BRACE, "}", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == ';') {
        next();
        t = Token(SEMICOLON, ";", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    if (c == ',') {
        next();
        t = Token(COMMA, ",", tokenIndex, startLine);
        tokenIndex++;
        return t;
    }
    
    next();
    string s = "";
    s += c;
    t = Token(UNKNOWN, s, tokenIndex, startLine);
    tokenIndex++;
    return t;
}

Token Lexer::nextToken() {
    while (pos < (int)input.length()) {
        skipSpace();
        
        if (pos >= (int)input.length()) {
            break;
        }
        
        char c = getChar();
        
        if (c == '/' && (peek() == '/' || peek() == '*')) {
            skipComments();
            // After skipping comments, continue to next iteration to skip spaces again
            // This handles the case where comment ends with newline
            continue;
        }
        
        if (c >= '0' && c <= '9') {
            return readNumber();
        }
        
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
            return readId();
        }
        
        return readOp();
    }
    
    Token t(END_OF_FILE, "", tokenIndex, line);
    tokenIndex++;
    return t;
}

vector<Token> Lexer::getAllTokens() {
    vector<Token> result;
    Token t;
    
    do {
        t = nextToken();
        result.push_back(t);
    } while (t.type != END_OF_FILE);
    
    return result;
}

void Lexer::output() {
    vector<Token> tokens = getAllTokens();
    
    for (int i = 0; i < (int)tokens.size(); i++) {
        if (tokens[i].type != END_OF_FILE) {
            cout << tokens[i].index << ":" << typeToStr(tokens[i].type) 
                      << ":\"" << tokens[i].value << "\"" << endl;
        }
    }
}

string Lexer::typeToStr(TokenType t) {
    if (t == INT) return "'int'";
    if (t == VOID) return "'void'";
    if (t == IF) return "'if'";
    if (t == ELSE) return "'else'";
    if (t == WHILE) return "'while'";
    if (t == BREAK) return "'break'";
    if (t == CONTINUE) return "'continue'";
    if (t == RETURN) return "'return'";
    if (t == IDENTIFIER) return "Ident";
    if (t == INTCONST) return "IntConst";
    if (t == PLUS) return "'+'";
    if (t == MINUS) return "'-'";
    if (t == MULTIPLY) return "'*'";
    if (t == DIVIDE) return "'/'";
    if (t == MODULO) return "'%'";
    if (t == ASSIGN) return "'='";
    if (t == EQUAL) return "'=='";
    if (t == NOT_EQUAL) return "'!='";
    if (t == LESS) return "'<'";
    if (t == LESS_EQUAL) return "'<='";
    if (t == GREATER) return "'>'";
    if (t == GREATER_EQUAL) return "'>='";
    if (t == AND) return "'&&'";
    if (t == OR) return "'||'";
    if (t == NOT) return "'!'";
    if (t == LEFT_PAREN) return "'('";
    if (t == RIGHT_PAREN) return "')'";
    if (t == LEFT_BRACE) return "'{'";
    if (t == RIGHT_BRACE) return "'}'";
    if (t == SEMICOLON) return "';'";
    if (t == COMMA) return "','";
    if (t == END_OF_FILE) return "EOF";
    return "UNKNOWN";
}
