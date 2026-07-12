#pragma once
#include"token.hpp"
#include<memory>

namespace ember{
    
    struct Expr{
        virtual ~Expr() = default;
    };

    struct LiteralExpr: Expr{
        Literal literal;
        LiteralExpr(Literal a): literal(std::move(a)) {}
    };

    struct GroupingExpr: Expr{
        std::unique_ptr<Expr> inner;
        GroupingExpr(std::unique_ptr<Expr> a): inner(std::move(a)) {}
    };

    struct UnaryExpr: Expr{
        std::unique_ptr<Expr> operand;
        Token operator_;
        UnaryExpr(std::unique_ptr<Expr> a, Token b): operand(std::move(a)), operator_(std::move(b)) {}
    };

    struct BinaryExpr: Expr{
        std::unique_ptr<Expr> left, right;
        Token operator_;
        BinaryExpr(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r, Token a): left(std::move(l)), right(std::move(r)), operator_(std::move(a)) {}
    };

}