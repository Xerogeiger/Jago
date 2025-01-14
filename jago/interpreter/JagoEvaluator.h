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
        JagoValue result = JagoValue(Jago::PrimitiveTypes::VOID, static_cast<void*>(nullptr));
        JagoScope* scope = nullptr;

    public:
        explicit JagoEvaluator();

        void visit(Literal& literal) override;
        void visit(BinaryExpression& binaryExpression) override;
        void visit(UnaryExpression& unaryExpression) override;
        void visit(ReturnStatement& returnStatement) override;
        void visit(AssignmentStatement &assignmentStatement) override;
        void visit(Program &program) override;
    };
} // Jago

#endif //JAGOEVALUATOR_H
