//
// Created by creep on 1/13/2025.
//

#ifndef EXPRESSIONNODES_H
#define EXPRESSIONNODES_H
#include <memory>
#include <string_view>

#include "ASTNode.h"

namespace Jago {

    class Expression : public ASTNode {
    public:
        virtual ~Expression() = default;
    };

    class Literal final : public Expression {
    public:
        explicit Literal(const std::string_view& value) : Expression(), value(value) {
        }

        void accept(Visitor& visitor) override;

        void prettyPrint(std::ostream &out, int indent) const override;

        std::string value;
    };

    class BinaryExpression : public Expression {
    public:
        BinaryExpression(std::unique_ptr<Expression> left,
                         std::unique_ptr<Expression> right,
                         const std::string_view& op)
            : left(std::move(left)), right(std::move(right)), op(op) {}

        void accept(Visitor& visitor) override;

        void prettyPrint(std::ostream &out, int indent) const override;

        std::unique_ptr<Expression> left;
        std::unique_ptr<Expression> right;
        std::string op;
    };

    class UnaryExpression : public Expression {
    public:
        UnaryExpression(std::unique_ptr<Expression> expression,
                        const std::string_view& op)
            : expression(std::move(expression)), op(op) {}

        void accept(Visitor& visitor) override;
        void prettyPrint(std::ostream &out, int indent) const override;

        std::unique_ptr<Expression> expression;
        std::string op;
    };
} // namespace Jago

#endif //EXPRESSIONNODES_H
