#include "lexer.hpp"
#include "ast_printer.hpp"
#include <iostream>
#include <string>

int main() {
    // --- B5 smoke test: hand-built tree for  -(1 + 2) * 3  (temporary) ---
    {
        using namespace ember;

        Token plus (TokenType::Plus,  "+", std::monostate{}, 1);
        Token minus(TokenType::Minus, "-", std::monostate{}, 1);
        Token star (TokenType::Star,  "*", std::monostate{}, 1);

        auto one   = std::make_unique<LiteralExpr>(1.0);
        auto two   = std::make_unique<LiteralExpr>(2.0);
        auto sum   = std::make_unique<BinaryExpr>(std::move(one), std::move(two), plus);
        auto group = std::make_unique<GroupingExpr>(std::move(sum));
        auto neg   = std::make_unique<UnaryExpr>(std::move(group), minus);
        auto three = std::make_unique<LiteralExpr>(3.0);
        auto root  = std::make_unique<BinaryExpr>(std::move(neg), std::move(three), star);

        AstPrinter printer;
        std::cout << printer.print(*root) << "\n";
    }
    // --- end smoke test ---

    std::cout << "Ember REPL (Milestone 1: lexer). Ctrl-Z + Enter to exit.\n";
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