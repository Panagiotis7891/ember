#pragma once

#include<ostream>
#include<string>
#include<variant>

namespace ember{
    enum class TokenType{
        LeftP, RightP, // ( )
        LeftCurl, RightCurl, // { }
        LeftBr, RightBr, // []
        Comma, Dot, Semicolon,
        Plus, Minus, Star, Slash,

        Not, NotEq, // ! !=
        Eq, EqEq, // = ==
        Gr, GrEq, // > >=
        Le, LeEq, // < <=

        //Literals

        Identifier, String, Number,

        //Keywords
        And, Or, True, False, If, Else, While, For, Nil, Var,
        Fun, Return, Print,

        Eof

    };

    using Literal = std::variant<std::monostate, std::string, double>;

    struct Token{
        TokenType type;
        std::string lexeme;
        Literal literal;
        int line;
        Token(TokenType a, const std::string &b, const Literal &c, int d): type(a), lexeme(b), literal(c), line(d) {}
    };

    const char* to_string(TokenType type);
    std::ostream& operator << (std::ostream& out, const Token &t);
}