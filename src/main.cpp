#include "lexer.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "Ember REPL (Milestone 1: lexer). Ctrl-D to exit.\n";
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        ember::Lexer lexer(line);
        for (const ember::Token& t : lexer.scan_tokens())
            std::cout << t << "\n";
    }
    std::cout << "\nBye.\n";
}