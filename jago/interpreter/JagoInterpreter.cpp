//
// Created by creep on 1/12/2025.
//

#include "JagoInterpreter.h"

#include <stack>

#include "../JagoGlobal.h"
#include "AST/ASTNode.h"
#include "AST/StatementNodes.h"

namespace Jago {
    ASTNode* JagoInterpreter::interpret(const std::vector<Jago::JagoToken> tokens) const {
        auto program = new Program();

        for (int x = 0; x < tokens.size(); x++) {
            if (tokens[x].TokenType == Token::JagoTokenType::Keyword) { // If it's a keyword, it's a statement
                program->statements.push_back(interpretStatement(tokens, x));
            } else { // Anything else is an expression
                program->statements.push_back(interpretExpression(tokens, x));
            }
        }

        return program;
    }

    std::unique_ptr<Statement> JagoInterpreter::interpretStatement(std::vector<Jago::JagoToken> tokens,
        int &index) const {
        if (tokens[index].TokenValue == "return") {
            index += 1;
            auto returnStatement = std::make_unique<ReturnStatement>(interpretExpression(tokens, index));
            return returnStatement;
        } else if (tokens[index].TokenType == Token::JagoTokenType::Keyword) {
            if (isPrimitiveType(tokens[index].TokenValue)) {
                auto typeName = tokens[index].TokenValue;

                Jago::PrimitiveTypes type;
                if (typeName == "int") {
                    type = Jago::PrimitiveTypes::INT;
                } else if (typeName == "float") {
                    type = Jago::PrimitiveTypes::FLOAT;
                } else if (typeName == "bool") {
                    type = Jago::PrimitiveTypes::BOOLEAN;
                } else if (typeName == "string") {
                    type = Jago::PrimitiveTypes::STRING;
                } else if (typeName == "char") {
                    type = Jago::PrimitiveTypes::CHAR;
                } else if (typeName == "long") {
                    type = Jago::PrimitiveTypes::LONG;
                } else if (typeName == "double") {
                    type = Jago::PrimitiveTypes::DOUBLE;
                } else if (typeName == "byte") {
                    type = Jago::PrimitiveTypes::BYTE;
                } else if (typeName == "short") {
                    type = Jago::PrimitiveTypes::SHORT;
                } else {
                    type = Jago::PrimitiveTypes::OBJECT;
                }

                index += 1;
                auto variableName = tokens[index].TokenValue;
                index += 2; // Skip the equals sign and move to the value
                auto value = interpretExpression(tokens, index);
                return std::make_unique<AssignmentStatement>(variableName, std::move(value), type);
            }
        }

        return nullptr;
    }

    std::unique_ptr<Expression>
    JagoInterpreter::interpretExpression(std::vector<Jago::JagoToken> tokens, int &index) const {
        std::stack<JagoToken> operatorStack; // Operators
        std::stack<std::unique_ptr<Expression>> expressionStack; // Expressions

        // Define operator precedence
        auto precedence = [](const std::string &opStr) -> int {
            for (const auto& op: Jago::DefaultJagoOperators) {
                if (op.OperatorSymbol == opStr) {
                    return op.Precedence;
                }
            }

            return -1;
        };

        // While not at the end of the statement
        while (tokens[index].TokenType != Token::JagoTokenType::StatementEnd) {
            if (tokens[index].TokenType == Token::JagoTokenType::NumberLiteral ||
                tokens[index].TokenType == Token::JagoTokenType::StringLiteral ||
                tokens[index].TokenType == Token::JagoTokenType::CharacterLiteral) {
                // Push literals directly to the expression stack
                expressionStack.push(std::make_unique<Literal>(tokens[index].TokenValue));
            } else if (tokens[index].TokenType == Token::JagoTokenType::Name) {
                expressionStack.push(std::make_unique<Variable>(tokens[index].TokenValue));
            } else if (tokens[index].TokenType == Token::JagoTokenType::Operator) {
                // While there is an operator on the stack with higher or equal precedence
                while (!operatorStack.empty() && precedence(operatorStack.top().TokenValue) >=
                                                         precedence(tokens[index].TokenValue)) {
                    if (operatorStack.empty() || expressionStack.size() < 2) {
                        throw std::runtime_error(
                                "Invalid state: operator or expression stack is empty");
                    }

                    auto op = operatorStack.top();
                    operatorStack.pop();

                    // Pop two expressions and create a BinaryExpression
                    auto right = std::move(expressionStack.top());
                    expressionStack.pop();

                    auto left = std::move(expressionStack.top());
                    expressionStack.pop();

                    expressionStack.push(std::make_unique<BinaryExpression>(
                            std::move(left), std::move(right), op.TokenValue));
                }

                // Push the current operator to the stack
                operatorStack.push(tokens[index]);
            }

            index++;
        }

        // Process remaining operators
        while (!operatorStack.empty()) {
            if (operatorStack.empty() || expressionStack.size() < 2) {
                throw std::runtime_error("Invalid state: operator or expression stack is empty");
            }

            auto op = operatorStack.top();
            operatorStack.pop();

            // Pop two expressions and create a BinaryExpression
            auto right = std::move(expressionStack.top());
            expressionStack.pop();

            auto left = std::move(expressionStack.top());
            expressionStack.pop();

            expressionStack.push(std::make_unique<BinaryExpression>(
                    std::move(left), std::move(right), op.TokenValue));
        }

        // The final expression on the stack is the result
        if (expressionStack.size() == 1) {
            return std::move(expressionStack.top());
        } else {
            return nullptr; // Error case
        }
    }

} // Jago