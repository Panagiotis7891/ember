#pragma once
#include"token.hpp"
#include<memory>

namespace ember{
    struct LiteralExpr;
    struct UnaryExpr;
    struct BinaryExpr;
    struct GroupingExpr;
    
    struct ExprVisitor{
        virtual void visit(LiteralExpr& a) = 0;
        virtual void visit(GroupingExpr& a) = 0;
        virtual void visit(UnaryExpr& a) = 0;
        virtual void visit(BinaryExpr& a) = 0;
        virtual ~ExprVisitor() = default;
    };


    struct Expr{
        virtual ~Expr() = default;
        virtual void accept(ExprVisitor &visitor) = 0;
    };

    struct LiteralExpr: Expr{
        Literal literal;
        LiteralExpr(Literal a): literal(std::move(a)) {}
        void accept(ExprVisitor& visitor) override{
            visitor.visit(*this);
        }
    };

    struct GroupingExpr: Expr{
        std::unique_ptr<Expr> inner;
        GroupingExpr(std::unique_ptr<Expr> a): inner(std::move(a)) {}
        void accept(ExprVisitor& visitor) override{
            visitor.visit(*this);
        }
    };

    struct UnaryExpr: Expr{
        std::unique_ptr<Expr> operand;
        Token operator_;
        UnaryExpr(std::unique_ptr<Expr> a, Token b): operand(std::move(a)), operator_(std::move(b)) {}
        void accept(ExprVisitor& visitor) override{
            visitor.visit(*this);
        }
    };

    struct BinaryExpr: Expr{
        std::unique_ptr<Expr> left, right;
        Token operator_;
        BinaryExpr(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r, Token a): left(std::move(l)), right(std::move(r)), operator_(std::move(a)) {}
        void accept(ExprVisitor& visitor) override{
            visitor.visit(*this);
        }
    };

}