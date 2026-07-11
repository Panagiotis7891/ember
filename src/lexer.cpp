#include"lexer.hpp"
#include<iostream>
#include<cctype>
#include<unordered_map>

namespace ember{

    Lexer::Lexer(const std::string &s): source(s) {}
    bool Lexer::is_at_end() const { return cur_ >= source.size(); }
    char Lexer::advance() { return source[cur_++]; }
    char Lexer::peek() const { return is_at_end() ? '\0' : source[cur_]; }
    char Lexer::peek_next() const { return is_at_end() ? '\0' : cur_ + 1 == source.size() ? '\0' : source[cur_ + 1]; }
    bool Lexer::match(char c){
        if(is_at_end() || c != source[cur_]) return false;
        advance();
        return true;
    }
    bool Lexer::had_error() const { return had_error_;}
    void Lexer::error(const std::string &message) { std::cerr << "[line " << line << "] Error: " << message << '\n'; had_error_ = true; }
    std::vector<Token> Lexer::scan_tokens(){
        while(!is_at_end()){
            start_ = cur_;
            scan_token();
        }
        start_ = cur_;
        add_token(TokenType::Eof);
        return tokens;
    }
    void Lexer::add_token(TokenType type, Literal literal){ tokens.emplace_back(type, source.substr(start_, cur_ - start_), literal, line); }
    void Lexer::scan_token(){
        char c = advance();
        switch(c){
            case '(': add_token(TokenType::LeftP); break;
            case ')': add_token(TokenType::RightP); break;
            case '{': add_token(TokenType::LeftCurl); break;
            case '}': add_token(TokenType::RightCurl); break;
            case '[': add_token(TokenType::LeftBr); break;
            case ']': add_token(TokenType::RightBr); break;
            case ',': add_token(TokenType::Comma); break;
            case '.': add_token(TokenType::Dot); break;
            case ';': add_token(TokenType::Semicolon); break;
            case '+': add_token(TokenType::Plus); break;
            case '-': add_token(TokenType::Minus); break;
            case '*': add_token(TokenType::Star); break;
            case '/':{ if(match('/')) while(peek() != '\n' && !is_at_end()) advance(); else add_token(TokenType::Slash); break; }
            case ' ': break;
            case '\r': break;
            case '\t': break;
            case '\n': line++; break;
            case '!':
                add_token(match('=') ? TokenType::NotEq : TokenType::Not);
                break;

            case '=':
                add_token(match('=') ? TokenType::EqEq : TokenType::Eq);
                break;

            case '>':
                add_token(match('=') ? TokenType::GrEq : TokenType::Gr);
                break;

            case '<':
                add_token(match('=') ? TokenType::LeEq : TokenType::Le);
                break;
            case '"': string_literal(); break;
            default:
                if(std::isdigit(static_cast<unsigned char>(c))) number_literal();
                else if(std::isalpha(static_cast<unsigned char>(c)) || c == '_') identifier_or_keyword();
                else error(std::string("Unexpected character '") + c + "'");
        }
    }

    void Lexer::string_literal(){
        std::string literal;
        char c;
        while(peek() != '"' && !is_at_end()){
            c = advance();
            if(c == '\n') line++;
            literal += c;
        }
        if(is_at_end()){
            error("You probably forgot \" at some point");
            return;
        }
        advance();
        add_token(TokenType::String, literal);
    }

    void Lexer::number_literal(){
        while(std::isdigit(static_cast<unsigned char>(peek()))) advance();
        if(peek() == '.' && std::isdigit(static_cast<unsigned char>(peek_next()))){
            advance();
            while(std::isdigit(static_cast<unsigned char>(peek()))) advance();
        }
        add_token(TokenType::Number, std::stod(source.substr(start_, cur_ - start_)));
    }

    void Lexer::identifier_or_keyword(){
        static const std::unordered_map<std::string, TokenType> keywords = {
            {"var", TokenType::Var},
            {"if", TokenType::If},
            {"else", TokenType::Else},
            {"and", TokenType::And},
            {"or", TokenType::Or},
            {"print", TokenType::Print},
            {"fun", TokenType::Fun},
            {"while", TokenType::While},
            {"for", TokenType::For},
            {"return", TokenType::Return},
            {"nil", TokenType::Nil},
            {"true", TokenType::True},
            {"false", TokenType::False}
        };
        while(std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') advance(); 
        auto it = keywords.find(source.substr(start_, cur_ - start_));
        if(it != keywords.end()) add_token(it->second);
        else add_token(TokenType::Identifier);
    }
}