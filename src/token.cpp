#include"token.hpp"

namespace ember{
    const char* to_string(TokenType type) {
        switch (type) {
            case TokenType::LeftP:      return "LEFT_PAREN";
            case TokenType::RightP:     return "RIGHT_PAREN";
            case TokenType::LeftCurl:   return "LEFT_BRACE";
            case TokenType::RightCurl:  return "RIGHT_BRACE";
            case TokenType::LeftBr:     return "LEFT_BRACKET";
            case TokenType::RightBr:    return "RIGHT_BRACKET";
            case TokenType::Comma:      return "COMMA";
            case TokenType::Dot:        return "DOT";
            case TokenType::Semicolon:  return "SEMICOLON";
            case TokenType::Plus:       return "PLUS";
            case TokenType::Minus:      return "MINUS";
            case TokenType::Star:       return "STAR";
            case TokenType::Slash:      return "SLASH";
            case TokenType::Not:        return "NOT";
            case TokenType::NotEq:      return "NOT_EQUAL";
            case TokenType::Eq:         return "EQUAL";
            case TokenType::EqEq:       return "EQUAL_EQUAL";
            case TokenType::Gr:         return "GREATER";
            case TokenType::GrEq:       return "GREATER_EQUAL";
            case TokenType::Le:         return "LESS";
            case TokenType::LeEq:       return "LESS_EQUAL";
            case TokenType::Identifier: return "IDENTIFIER";
            case TokenType::String:     return "STRING";
            case TokenType::Number:     return "NUMBER";
            case TokenType::And:        return "AND";
            case TokenType::Or:         return "OR";
            case TokenType::True:       return "TRUE";
            case TokenType::False:      return "FALSE";
            case TokenType::If:         return "IF";
            case TokenType::Else:       return "ELSE";
            case TokenType::While:      return "WHILE";
            case TokenType::For:        return "FOR";
            case TokenType::Nil:        return "NIL";
            case TokenType::Var:        return "VAR";
            case TokenType::Fun:        return "FUN";
            case TokenType::Return:     return "RETURN";
            case TokenType::Print:      return "PRINT";
            case TokenType::Eof:        return "EOF";
        }
        return "UNKNOWN";
    }

    std::ostream& operator << (std::ostream& out, const Token &t){
        out << to_string(t.type) << " '" << t.lexeme << "'";
        if(std::holds_alternative<double>(t.literal)) out << " (" << std::get<double>(t.literal) << ')';
        else if(std::holds_alternative<std::string>(t.literal)) out << " (" << std::get<std::string>(t.literal) << ')';
        return out;
    }


}