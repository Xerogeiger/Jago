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
                index += 1;
                auto variableName = tokens[index].TokenValue;
                index += 2; // Skip the equals sign and move to the value
                auto value = interpretExpression(tokens, index);
                return std::make_unique<AssignmentStatement>(variableName, std::move(value));
            }
        }

        return nullptr;
    }

    std::unique_ptr<Expression> JagoInterpreter::interpretExpression(std::vector<Jago::JagoToken> tokens, int &index) const {
        std::stack<JagoToken> operatorStack; // Operators
        std::stack<std::unique_ptr<Expression>> expressionStack; // Expressions

        // Define operator precedence
        auto precedence = [](const std::string &op) -> int {
            if (op == "+" || op == "-") return 1;  // Low precedence
            if (op == "*" || op == "/") return 2;  // Medium precedence
            if (op == "^") return 3;              // High precedence
            return 0;                             // Unknown operator
        };

        // While not at the end of the statement
        while (tokens[index].TokenType != Token::JagoTokenType::StatementEnd) {
            if (tokens[index].TokenType == Token::JagoTokenType::NumberLiteral ||
                tokens[index].TokenType == Token::JagoTokenType::StringLiteral ||
                tokens[index].TokenType == Token::JagoTokenType::CharacterLiteral) {
                // Push literals directly to the expression stack
                expressionStack.push(std::make_unique<Literal>(tokens[index].TokenValue));
            } else if (tokens[index].TokenType == Token::JagoTokenType::Operator) {
                // While there is an operator on the stack with higher or equal precedence
                while (!operatorStack.empty() &&
                       precedence(operatorStack.top().TokenValue) >= precedence(tokens[index].TokenValue)) {
                    auto op = operatorStack.top();
                    operatorStack.pop();

                    // Pop two expressions and create a BinaryExpression
                    auto right = std::move(expressionStack.top());
                    expressionStack.pop();

                    auto left = std::move(expressionStack.top());
                    expressionStack.pop();

                    expressionStack.push(std::make_unique<BinaryExpression>(std::move(left), std::move(right), op.TokenValue));
                }

                // Push the current operator to the stack
                operatorStack.push(tokens[index]);
            }

            index++;
        }

        // Process remaining operators
        while (!operatorStack.empty()) {
            auto op = operatorStack.top();
            operatorStack.pop();

            // Pop two expressions and create a BinaryExpression
            auto right = std::move(expressionStack.top());
            expressionStack.pop();

            auto left = std::move(expressionStack.top());
            expressionStack.pop();

            expressionStack.push(std::make_unique<BinaryExpression>(std::move(left), std::move(right), op.TokenValue));
        }

        // The final expression on the stack is the result
        if (expressionStack.size() == 1) {
            return std::move(expressionStack.top());
        } else {
            return nullptr;  // Error case
        }
    }

} // Jago