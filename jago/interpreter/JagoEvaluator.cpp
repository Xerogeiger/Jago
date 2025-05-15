//
// Created by creep on 1/13/2025.
//

#include "JagoEvaluator.h"

#include <iostream>

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

            result = JagoValue(value);
        } else if (literal.value.starts_with('\'')) {
            result = JagoValue(static_cast<int8_t>(literal.value[1]));
        } else if (literal.value == "true" || literal.value == "false") {
            result = JagoValue(literal.value == "true");
        } else if (literal.value.contains('.')) {
            result = JagoValue(std::stod(std::string(literal.value)));
        } else {
            result = JagoValue(std::stoi(std::string(literal.value)));
        }
    }
    void JagoEvaluator::visit(Variable &variable) {
        result = scope->getVariable(variable.name);
        resultVariableName = variable.name;
    }

    void JagoEvaluator::visit(BinaryExpression &binaryExpression) {
        binaryExpression.left->accept(*this);
        JagoValue left = result;
        std::string leftVariableName = resultVariableName;

        binaryExpression.right->accept(*this);
        JagoValue right = result;

        auto op = binaryExpression.op;

        if (op == "+") {
            if (left == Type::STRING || right == Type::STRING) {
                auto leftStr = left.asString();
                auto rightStr = right.asString();
                result = JagoValue(new std::string(leftStr + rightStr));
            } else if (left == Type::DOUBLE || right == Type::DOUBLE) {
                result = JagoValue(left.asDouble() + right.asDouble());
            } else {
                result = JagoValue(left.asLong() + right.asLong());
            }
        } else if (op == "*") {
            if (left == Type::DOUBLE || right == Type::DOUBLE) {
                result = JagoValue(left.asDouble() * right.asDouble());
            } else {
                result = JagoValue(left.asLong() * right.asLong());
            }
        } else if (op == "-") {
            if (left == Type::DOUBLE || right == Type::DOUBLE) {
                result = JagoValue(left.asDouble() - right.asDouble());
            } else {
                result = JagoValue(left.asLong() - right.asLong());
            }
        } else if (op == "/") {
            if (left == Type::DOUBLE || right == Type::DOUBLE) {
                result = JagoValue(left.asDouble() / right.asDouble());
            } else {
                result = JagoValue(left.asLong() / right.asLong());
            }
        } else if (op == "=") {
            if (scope->hasVariable(leftVariableName)) {
                JagoValue currentValue = scope->getVariable(leftVariableName);
                this->scope->setVariable(leftVariableName, right.castToType(currentValue.type));
            } else {
                throw std::runtime_error("Cannot assign to undeclared variable");
            }
        } else if (op == "%") {
            result = JagoValue(left.asLong() % right.asLong());
        } else if (op == "==") {
            result = JagoValue(left == right);
        } else if (op == "!=") {
            result = JagoValue(left != right);
        } else if (op == ">") {
            result = JagoValue(left > right);
        } else if (op == "<") {
            result = JagoValue(left < right);
        } else if (op == ">=") {
            result = JagoValue(left >= right);
        } else if (op == "<=") {
            result = JagoValue(left <= right);
        }
    }

    void JagoEvaluator::visit(UnaryExpression &unaryExpression) {
    }

    void JagoEvaluator::visit(ReturnStatement &returnStatement) {
        returnStatement.value->accept(*this);
    }

    void JagoEvaluator::visit(AssignmentStatement &assignmentStatement) {
        assignmentStatement.value->accept(*this);

        JagoValue variableValue;

        switch (assignmentStatement.type) {
            case PrimitiveTypes::INT:
                variableValue = result.asInt();
                break;
            case PrimitiveTypes::DOUBLE:
                variableValue = result.asDouble();
                break;
            case PrimitiveTypes::STRING:
                variableValue = result.asString();
                break;
            default:;
        }

        scope->setVariable(assignmentStatement.variableName, variableValue);
    }

    void JagoEvaluator::visit(Program &program) {
        for (const auto &statement: program.statements) {
            statement->accept(*this);
        }
    }
    void JagoEvaluator::visit(MethodDeclarationStatement methodStatement) {
        scope->setFunction(methodStatement.name,
                           JagoMethod(std::move(methodStatement.body), methodStatement.parameters));
    }
    void JagoEvaluator::visit(const MethodCallExpression &methodCallExpression) {
        auto newScope = JagoScope(scope);

        for (const auto &param: methodCallExpression.arguments) {
            param->accept(*this);
            newScope.setVariable(resultVariableName, result);
        }

        scope->getFunction(methodCallExpression.name).invoke(newScope);
    }

    void JagoEvaluator::dump(std::ostream &out) const {
        out << "Last Result: " << result << std::endl;

        this->scope->dump(out);
    }
} // Jago