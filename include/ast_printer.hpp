#pragma once
#include"expr.hpp"
#include<string>

namespace ember{
    class AstPrinter: public ExprVisitor{
        public:
        void visit(LiteralExpr &a) override{
            if(std::holds_alternative<std::string>(a.literal)) accumulator += std::get<std::string>(a.literal);
            else if(std::holds_alternative<double>(a.literal)) accumulator += std::to_string(std::get<double>(a.literal));
            else accumulator += "nil";
        }
        void visit(GroupingExpr &a) override{
            accumulator += "(group ";
            a.inner->accept(*this);
            accumulator += ")";
        }
        void visit(UnaryExpr &a) override{
            accumulator += "(" + a.operator_.lexeme + " ";
            a.operand->accept(*this);
            accumulator += ")";
        }
        void visit(BinaryExpr &a) override{
            accumulator += "(" + a.operator_.lexeme + " ";
            a.left->accept(*this);
            accumulator += " ";
            a.right->accept(*this);
            accumulator += ")";
        }

        std::string print(Expr &expr){
            accumulator.clear();
            expr.accept(*this);
            return std::move(accumulator);
        }

        private:
        std::string accumulator;
    };


}