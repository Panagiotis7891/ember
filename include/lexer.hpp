#pragma once

#include"token.hpp"
#include<string>
#include<vector>

namespace ember{
    class Lexer{
        public:
        Lexer(const std::string &s);
        std::vector<Token> scan_tokens();
        bool had_error() const;

        private:
        std::string source;
        std::vector<Token> tokens;
        std::size_t start_{}, cur_{};
        int line{1};
        bool had_error_{};
        bool is_at_end() const;
        char advance();
        char peek() const;
        char peek_next() const;
        bool match(char c);
        void scan_token();
        void add_token(TokenType type, Literal literal = std::monostate{});
        void string_literal();
        void number_literal();
        void identifier_or_keyword();
        void error(const std::string &message);
    };






}