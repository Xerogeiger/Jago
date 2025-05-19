//
// Created by creep on 1/13/2025.
//

#ifndef STATEMENTNODES_H
#define STATEMENTNODES_H
#include <memory>

#include "../../PrimitiveTypes.h"
#include "../JagoMethod.h"
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
        Jago::PrimitiveTypes type;

        explicit AssignmentStatement(std::string_view variableName, std::unique_ptr<Expression> value, Jago::PrimitiveTypes type)
            : Statement(), variableName(variableName), value(std::move(value)), type(type) {
        }

        void accept(Visitor& visitor) override;

        void prettyPrint(std::ostream &out, int indent) const override;
    };

    class MethodDeclarationStatement final : public Statement {
    public:
        std::string name;
        JagoType returnType;
        std::vector<JagoParameter> parameters;
        std::unique_ptr<ASTNode> body;

        explicit MethodDeclarationStatement(std::string_view name, JagoType returnType, std::vector<JagoParameter> parameters, std::unique_ptr<ASTNode> body)
            : Statement(), name(name), returnType(returnType), parameters(std::move(parameters)), body(std::move(body)) {
        }

        void accept(Visitor& visitor) override;
        void prettyPrint(std::ostream &out, int indent) const override;
    };

    class ScopeBody final : public Statement {
    private:
        std::vector<std::unique_ptr<ASTNode>> statements;

    public:
        explicit ScopeBody(std::vector<std::unique_ptr<ASTNode>> statements)
            : Statement(), statements(std::move(statements)) {
        }

        void accept(Visitor& visitor) override;
        void prettyPrint(std::ostream &out, int indent) const override;
    };

    class IfStatement final : public Statement {
    public:
        std::unique_ptr<ASTNode> trueCase;
        std::unique_ptr<ASTNode> falseCase;
        std::unique_ptr<Expression> condition;

        explicit IfStatement(std::unique_ptr<ASTNode> trueCase, std::unique_ptr<ASTNode> falseCase, std::unique_ptr<Expression> condition)
            : Statement(), trueCase(std::move(trueCase)), falseCase(std::move(falseCase)), condition(std::move(condition)) {
        }

        void accept(Visitor& visitor) override;
        void prettyPrint(std::ostream &out, int indent) const override;
    };
}

#endif //STATEMENTNODES_H
