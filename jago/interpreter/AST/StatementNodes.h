//
// Created by creep on 1/13/2025.
//

#ifndef STATEMENTNODES_H
#define STATEMENTNODES_H
#include <memory>

#include "ASTNode.h"
#include "ExpressionNodes.h"

namespace Jago {

    class Statement : public ASTNode {
    public:
        ~Statement() override = default;
    };

    class ReturnStatement final : public Statement {
    public:
        explicit ReturnStatement(std::unique_ptr<Expression> value)
            : Statement(), value(std::move(value)) {
        }

        void accept(Visitor& visitor) override;

        void prettyPrint(std::ostream &out, int indent) const override;

        std::unique_ptr<Expression> value;
    };

    class AssignmentStatement final : public Statement {
    public:
        std::string variableName;
        std::unique_ptr<Expression> value;

        explicit AssignmentStatement(std::string_view variableName, std::unique_ptr<Expression> value)
            : Statement(), variableName(variableName), value(std::move(value)) {
        }

        void accept(Visitor& visitor) override;

        void prettyPrint(std::ostream &out, int indent) const override;
    };
}

#endif //STATEMENTNODES_H
