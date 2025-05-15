//
// Created by creep on 1/13/2025.
//

#ifndef JAGOEVALUATOR_H
#define JAGOEVALUATOR_H
#include "JagoScope.h"
#include "JagoValue.h"
#include "AST/Visitor.h"

namespace Jago {

    class JagoEvaluator final : public Visitor {
    protected:
        std::string resultVariableName;
        JagoValue result = JagoValue();
        JagoScope* scope = nullptr;

    public:
        explicit JagoEvaluator();

        void visit(Literal& literal) override;
        void visit(Variable &variable) override;
        void visit(BinaryExpression& binaryExpression) override;
        void visit(UnaryExpression& unaryExpression) override;
        void visit(ReturnStatement& returnStatement) override;
        void visit(AssignmentStatement &assignmentStatement) override;
        void visit(Program &program) override;
        void visit(MethodDeclarationStatement methodStatement) override;
        void visit(const MethodCallExpression &methodCallExpression) override;

        [[nodiscard]] JagoValue getResult() const {
            return result;
        }

        [[nodiscard]] std::string getResultVariableName() const {
            return resultVariableName;
        }

        void dump(std::ostream &out) const;
    };
} // Jago

#endif //JAGOEVALUATOR_H
