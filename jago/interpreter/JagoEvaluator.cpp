//
// Created by creep on 1/13/2025.
//

#include "JagoEvaluator.h"

#include <iostream>

#include "../PrimitiveTypes.h"
#include "AST/ExpressionNodes.h"
#include "AST/StatementNodes.h"
#include "JagoClass.h"

namespace Jago {
    JagoEvaluator::JagoEvaluator() {
        this->globalScope = std::make_shared<JagoScope>(nullptr); // Global scope
        this->globalScope->setVariable("true", JagoValue(true));
        this->globalScope->setVariable("false", JagoValue(false));
        this->currentScope = this->globalScope;
        defineGlobalFunctions();
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
            result = JagoValue(std::stod(literal.value));
        } else {
            result = JagoValue(std::stoi(literal.value));
        }
    }
    void JagoEvaluator::visit(Variable &variable) {
        result = currentScope->getVariable(variable.name);
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
                result = JagoValue(leftStr + rightStr);
            } else if (left == Type::DOUBLE || right == Type::DOUBLE) {
                result = JagoValue(left.asDouble() + right.asDouble());
            } else {
                result = JagoValue(left.asLong() + right.asLong());
            }
        } else if (op == "*") {
            if (left == Type::STRING || right == Type::STRING) {
                auto string = left == Type::STRING ? left.asString() : right.asString();
                auto number = left == Type::STRING ? right.asLong() : left.asLong();
                std::string resultString;
                for (int i = 0; i < number; i++) {
                    resultString += string;
                }
                result = JagoValue(resultString);
            } else
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
            if (currentScope->hasVariable(leftVariableName)) {
                JagoValue currentValue = currentScope->getVariable(leftVariableName);
                this->currentScope->setVariable(leftVariableName, right.castToType(currentValue.type));
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
        } else if (op == "+=") {
            binaryExpression.left->accept(*this);
            auto leftVariableName = resultVariableName;
            binaryExpression.right->accept(*this);
            auto right = result;
            auto left = currentScope->getVariable(leftVariableName);
            if (left == Type::STRING || right == Type::STRING) {
                auto leftStr = left.asString();
                auto rightStr = right.asString();
                result = JagoValue(leftStr + rightStr);
            } else if (left == Type::DOUBLE || right == Type::DOUBLE) {
                result = JagoValue(left.asDouble() + right.asDouble());
            } else {
                result = JagoValue(left.asLong() + right.asLong());
            }
            if (currentScope->hasVariable(leftVariableName)) {
                JagoValue currentValue = currentScope->getVariable(leftVariableName);
                this->currentScope->setVariable(leftVariableName, result.castToType(currentValue.type));
            } else {
                throw std::runtime_error("Cannot assign to undeclared variable");
            }
        }
    }

    void JagoEvaluator::visit(UnaryExpression &unaryExpression) {
    }

    void JagoEvaluator::visit(ReturnStatement &returnStatement) {
        returnStatement.value->accept(*this);

        throw ReturnSignal{result};
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

        currentScope->setVariable(assignmentStatement.variableName, variableValue);
    }

    void JagoEvaluator::visit(Program &program) {
        for (const auto &statement: program.statements) {
            statement->accept(*this);
        }
    }
    void JagoEvaluator::visit(MethodDeclarationStatement methodStatement) {
        currentScope->setFunction(methodStatement.name,
                            std::make_shared<JagoMethod>(methodStatement.name, std::move(methodStatement.body), methodStatement.parameters));
    }

    struct ScopeGuard {
        JagoEvaluator& E;
        std::shared_ptr<JagoScope> old;
        ScopeGuard(JagoEvaluator& e, std::shared_ptr<JagoScope> nxt)
          : E(e), old(std::move(e.currentScope)) {
            e.currentScope = std::move(nxt);
        }
        ~ScopeGuard() { E.currentScope = std::move(old); }
    };


    void JagoEvaluator::visit(const MethodCallExpression &methodCallExpression) {
        auto parent = currentScope;

        auto function = currentScope->getFunction(methodCallExpression.name);

        auto child  = std::make_shared<JagoScope>(parent);
        ScopeGuard g{*this, child};

        int index = 0;

        for (const auto &param: methodCallExpression.arguments) {
            param->accept(*this);

            if (index >= function->getParameters().size()) {
                throw std::runtime_error("Too many arguments");
            }

            child->setVariable(function->getParameters()[index++].name, result);
        }

        try {
            this->result = function->invoke(*this, child);
        } catch (ReturnSignal &signal) {
            this->result = signal.value;
            return;
        }
    }

    void JagoEvaluator::defineGlobalFunctions() {
        currentScope->setFunction("print", std::make_shared<NativeMethod>(
            "print",
                std::vector<JagoParameter>{JagoParameter{Jago::Type::STRING, "value"}},
                [](std::shared_ptr<JagoScope> scope) {
                    auto value = scope->getVariable("value");
                    std::cout << "STD Out: " << value.asString() << std::endl;
                    return JagoValue();
                }));
    }

    void JagoEvaluator::dump(std::ostream &out) const {
        out << "Last Result: " << result << std::endl;

        currentScope->dump(out);
    }
    void JagoEvaluator::visit(const IncrementalForStatement &forStatement) {
        forStatement.initialization->accept(*this);

        forStatement.condition->accept(*this);
        auto condition = result.asLong();

        try {
            while (condition) {
                try {
                    forStatement.body->accept(*this);
                } catch (ContinueSignal &signal) {
                    std::cout << "Loop continuing" << std::endl;
                }
                forStatement.increment->accept(*this);
                forStatement.condition->accept(*this);
                condition = result.asLong();
            }
        } catch (BreakSignal &signal) {
            std::cout << "Break signal" << std::endl;
        }
    }
    void JagoEvaluator::visit(const ClassDeclarationStatement &literal) {
        std::shared_ptr<JagoClass> jagoClass = std::make_shared<JagoClass>(literal.name);
        for (const auto &method: literal.methods) {
            jagoClass->addMethod(method);
        }
        currentScope->setClass(literal.name, jagoClass);
    }
    void JagoEvaluator::visit(const NewExpression &literal) {
        
    }

    void JagoEvaluator::visit(const IfStatement &statement) {
        statement.condition->accept(*this);
        auto condition = result.asLong();
        if (condition) {
            statement.trueCase->accept(*this);
        } else {
            if (statement.falseCase) {
                statement.falseCase->accept(*this);
            }
        }
    }

    void JagoEvaluator::visit(const ContinueStatement &continueStatement) {
        throw ContinueSignal{};
    }
} // Jago