#include "parser.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string input;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        input += line + "\n";
    }
    
    Parser parser(input);
    parser.parse();
    parser.printErrors();
    
    return 0;
}

