//
// Created by creep on 1/13/2025.
//

#ifndef VISITOR_H
#define VISITOR_H
#include "StatementNodes.h"

namespace Jago {

    class Literal;
    class Variable;
    class BinaryExpression;
    class UnaryExpression;
    class ReturnStatement;
    class AssignmentStatement;
    class Program;

    class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void visit(Literal& literal) = 0;
        virtual void visit(Variable& variable) = 0;
        virtual void visit(BinaryExpression& binaryExpression) = 0;
        virtual void visit(UnaryExpression& unaryExpression) = 0;
        virtual void visit(ReturnStatement& returnStatement) = 0;
        virtual void visit(AssignmentStatement& assignmentStatement) = 0;
        virtual void visit(Program &program) = 0;
        virtual void visit(MethodDeclarationStatement literal) = 0;
        virtual void visit(const MethodCallExpression &literal) = 0;
        virtual JagoValue getResult() = 0;
        virtual void visit(const IfStatement &statement) = 0;
    };

}

#endif //VISITOR_H
