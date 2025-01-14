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

    std::unique_ptr<Expression> JagoInterpreter::interpretExpression(std::vector<Jago::JagoToken> tokens,
        int &index) const {
        std::vector<JagoToken> operators;
        std::stack<std::unique_ptr<Expression>> expressions; //All expressions in the current statement

        while (tokens[index].TokenType != Token::JagoTokenType::StatementEnd) {
            if (tokens[index].TokenType == Token::JagoTokenType::NumberLiteral) {
                expressions.push(std::make_unique<Literal>(tokens[index].TokenValue));
            } else if (tokens[index].TokenType == Token::JagoTokenType::StringLiteral) {
                expressions.push(std::make_unique<Literal>(tokens[index].TokenValue));
            } else if (tokens[index].TokenType == Token::JagoTokenType::CharacterLiteral) {
                expressions.push(std::make_unique<Literal>(tokens[index].TokenValue));
            } else if (tokens[index].TokenType == Token::JagoTokenType::Operator) {
                operators.push_back(tokens[index]);
            }

            index++;
        }

        while (!operators.empty()) {
            auto op = operators.back();
            operators.pop_back();

            auto right = std::move(expressions.top());
            expressions.pop();

            auto left = std::move(expressions.top());
            expressions.pop();

            expressions.push(std::make_unique<BinaryExpression>(std::move(left), std::move(right), op.TokenValue));
        }

        if (expressions.size() == 1) {
            return std::move(expressions.top());
        } else {
            return nullptr;
        }
    }
} // Jago