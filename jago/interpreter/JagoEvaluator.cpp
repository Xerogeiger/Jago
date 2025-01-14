//
// Created by creep on 1/13/2025.
//

#include "JagoEvaluator.h"

#include "../PrimitiveTypes.h"
#include "AST/ExpressionNodes.h"
#include "AST/StatementNodes.h"

namespace Jago {
    JagoEvaluator::JagoEvaluator() {
        this->scope = new JagoScope(); // Global scope
    }

    void JagoEvaluator::visit(Literal &literal) {
        if (literal.value.starts_with('\"')) {
            auto value = std::string(literal.value.substr(1, literal.value.size() - 2));

            result = JagoValue(Jago::PrimitiveTypes::STRING, &value);
        } else if (literal.value.starts_with('\'')) {
            result = JagoValue(Jago::PrimitiveTypes::CHAR, static_cast<int8_t>(literal.value[1]));
        } else if (literal.value == "true" || literal.value == "false") {
            result = JagoValue(Jago::PrimitiveTypes::BOOLEAN, literal.value == "true");
        } else if (literal.value.contains('.')) {
            result = JagoValue(Jago::PrimitiveTypes::DOUBLE, std::stod(std::string(literal.value)));
        } else {
            result = JagoValue(Jago::PrimitiveTypes::INT, std::stoi(std::string(literal.value)));
        }
    }

    void JagoEvaluator::visit(BinaryExpression &binaryExpression) {
        binaryExpression.left->accept(*this);
        JagoValue left = result;

        binaryExpression.right->accept(*this);
        JagoValue right = result;

        auto op = binaryExpression.op;

        if (op == "+") {
            if (left == STRING || right == STRING) {
                auto leftStr = left.asString();
                auto rightStr = right.asString();
                result = JagoValue(Jago::PrimitiveTypes::STRING, new std::string(leftStr + rightStr));
            } else if (left == DOUBLE || right == DOUBLE) {
                result = JagoValue(Jago::PrimitiveTypes::DOUBLE, left.asDouble() + right.asDouble());
            } else {
                result = JagoValue(Jago::PrimitiveTypes::LONG, left.asInt() + right.asInt());
            }
        } else if (op == "*") {
            if (left == DOUBLE || right == DOUBLE) {
                result = JagoValue(Jago::PrimitiveTypes::DOUBLE, left.asDouble() * right.asDouble());
            } else {
                result = JagoValue(Jago::PrimitiveTypes::LONG, left.asInt() * right.asInt());
            }
        }
    }

    void JagoEvaluator::visit(UnaryExpression &unaryExpression) {
    }

    void JagoEvaluator::visit(ReturnStatement &returnStatement) {
        returnStatement.value->accept(*this);
    }

    void JagoEvaluator::visit(AssignmentStatement &assignmentStatement) {
        assignmentStatement.value->accept(*this);
        scope->setVariable(assignmentStatement.variableName, result);
    }

    void JagoEvaluator::visit(Program &program) {
        for (const auto &statement: program.statements) {
            statement->accept(*this);
        }
    }
    void JagoEvaluator::dump(std::ostream &out) const {
        out << "Last Result: " << result << std::endl;

        this->scope->dump(out);
    }
} // Jago