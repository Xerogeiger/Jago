//
// Created by creep on 1/12/2025.
//

#include "JagoInterpreter.h"

#include <stack>

#include "../JagoGlobal.h"
#include "AST/ASTNode.h"
#include "AST/StatementNodes.h"
#include "JagoMethod.h"

namespace Jago {
    ASTNode* JagoInterpreter::interpret(const std::vector<Jago::JagoToken> tokens) const {
        auto program = new Program();

        int index = 0;
        while (index < tokens.size()) {
            std::cout << "Processing token: " << tokens[index].TokenValue << std::endl;

            if (tokens[index].TokenType == Token::JagoTokenType::Keyword)
                program->statements.push_back(interpretStatement(tokens, index));
            else
                program->statements.push_back(interpretExpression(tokens, index));

            if (tokens[index].TokenType == Token::JagoTokenType::StatementEnd) {
                index ++;
            }
        }

        return program;
    }

    JagoType getTypeFromString(std::string typeName) {
        if (Jago::Type::INT.getTypeName() == typeName) {
            return Jago::Type::INT;
        } else if (Type::FLOAT.getTypeName() == typeName) {
            return Type::FLOAT;
        } else if (Type::BOOLEAN.getTypeName() == typeName) {
            return Type::BOOLEAN;
        } else if (Type::STRING.getTypeName() == typeName) {
            return Type::STRING;
        } else if (Type::CHAR.getTypeName() == typeName) {
            return Type::CHAR;
        } else if (Type::LONG.getTypeName() == typeName) {
            return Type::LONG;
        } else if (Type::DOUBLE.getTypeName() == typeName) {
            return Type::DOUBLE;
        } else if (Type::BYTE.getTypeName() == typeName) {
            return Type::BYTE;
        } else if (Type::SHORT.getTypeName() == typeName) {
            return Type::SHORT;
        } else if (Type::VOID.getTypeName() == typeName) {
            return Type::VOID;
        } else {
            return Type::OBJECT;
        }
    }

    std::unique_ptr<Statement> JagoInterpreter::interpretStatement(std::vector<Jago::JagoToken> tokens,
        int &index) const {
        if (tokens[index].TokenValue == "return") {
            index += 1;
            auto returnStatement = std::make_unique<ReturnStatement>(interpretExpression(tokens, index));
            return returnStatement;
        } else if (tokens[index].TokenType == Token::JagoTokenType::Keyword) {
            if (tokens[index].TokenValue == "define") {
                //Method declaration goes
                //define returnType methodName(parameters) scopeOpen statements scopeClose
                index += 1; // Skip the define keyword
                auto returnType = tokens[index].TokenValue;
                index += 1; // Skip the return type
                auto methodName = tokens[index].TokenValue;
                index += 1; // Skip the method name

                std::vector<JagoParameter> parameters;

                if (tokens[index].TokenType == Token::JagoTokenType::ParenthesisOpen) {
                    index += 1; // Skip the parenthesis open
                    while (tokens[index].TokenType != Token::JagoTokenType::ParenthesisClose) {
                        std::string typeToken = tokens[index].TokenValue;       // type
                        std::string nameToken = tokens[index + 1].TokenValue;     // parameter name
                        parameters.push_back(JagoParameter{ getTypeFromString(typeToken), nameToken });
                        index += 2;
                        // Optionally handle a comma separator if present
                        if (tokens[index].TokenType == Token::JagoTokenType::Operator && tokens[index].TokenValue == ",")
                            index++;
                    }

                    index += 1; // Skip the parenthesis close
                }

                if (tokens[index].TokenType == Token::JagoTokenType::ScopeOpen) {
                    index += 1; // Skip the scope open
                    std::vector<std::unique_ptr<ASTNode>> statements;
                    while (tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
                        statements.push_back(interpretStatement(tokens, index));
                        if (tokens[index].TokenType == Token::JagoTokenType::StatementEnd) {
                            index += 1;
                        }
                    }

                    index += 1; // Skip the scope close



                    return std::make_unique<MethodDeclarationStatement>(methodName, getTypeFromString(returnType), parameters, std::make_unique<ScopeBody>(std::move(statements)));
                }
            } else if (isPrimitiveType(tokens[index].TokenValue)) {
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
JagoInterpreter::interpretExpression(std::vector<Jago::JagoToken> tokens, int &index) {
    std::stack<JagoToken> operatorStack; // Operators
    std::stack<std::unique_ptr<Expression>> expressionStack; // Expression

    // Define operator precedence
    auto precedence = [](const std::string &opStr) -> int {
        for (const auto& op: Jago::DefaultJagoOperators) {
            if (op.OperatorSymbol == opStr) {
                return op.Precedence;
            }
        }
        return -1; // Invalid operator precedence
    };

    // While not at the end of the statement
    while (tokens[index].TokenType != Token::JagoTokenType::StatementEnd &&
        tokens[index].TokenType != Token::JagoTokenType::ScopeClose &&
        !(tokens[index].TokenType == Token::JagoTokenType::Operator && tokens[index].TokenValue == ",")) {

        std::cout << "Processing token: " << tokens[index].TokenValue << std::endl;

        if (tokens[index].TokenType == Token::JagoTokenType::NumberLiteral ||
            tokens[index].TokenType == Token::JagoTokenType::StringLiteral ||
            tokens[index].TokenType == Token::JagoTokenType::CharacterLiteral) {
            // Push literals directly to the expression stack
            expressionStack.push(std::make_unique<Literal>(tokens[index].TokenValue));
        } else if (tokens[index].TokenType == Token::JagoTokenType::Name) {
            // Push variable names to the expression stack

            if (tokens[index+1].TokenType == Token::JagoTokenType::ParenthesisOpen) {
                std::string methodName = tokens[index].TokenValue;

                // Function call
                index += 1; // Skip the parenthesis open
                std::vector<std::unique_ptr<Expression>> arguments;
                while (tokens[index].TokenType != Token::JagoTokenType::ParenthesisClose) {
                    arguments.push_back(interpretExpression(tokens, index));
                    if (tokens[index].TokenType == Token::JagoTokenType::Operator && tokens[index].TokenValue == ",") {
                        index += 1;
                    }
                }

                index += 1; // Skip the parenthesis close

                expressionStack.push(std::make_unique<MethodCallExpression>(methodName, std::move(arguments)));
            } else {
                expressionStack.push(std::make_unique<Variable>(tokens[index].TokenValue));
                index++;  // Increment index to avoid processing the same token again
            }
            continue;
        } else if (tokens[index].TokenType == Token::JagoTokenType::Operator) {
            // While there is an operator on the stack with higher or equal precedence
            while (!operatorStack.empty() && operatorStack.top().TokenType != Token::JagoTokenType::ParenthesisOpen &&
                   precedence(operatorStack.top().TokenValue) >= precedence(tokens[index].TokenValue)) {
                if (expressionStack.size() < 2) {
                    throw std::runtime_error("Invalid state: insufficient expressions for operator " + tokens[index].TokenValue);
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
        } else if (tokens[index].TokenType == Token::JagoTokenType::ParenthesisOpen) {
            // Push opening parenthesis to the operator stack
            operatorStack.push(tokens[index]);
        } else if (tokens[index].TokenType == Token::JagoTokenType::ParenthesisClose) {
            // Process until an opening parenthesis is found
            while (!operatorStack.empty() && operatorStack.top().TokenType != Token::JagoTokenType::ParenthesisOpen) {
                if (expressionStack.size() < 2) {
                    throw std::runtime_error("Invalid state: insufficient expressions for operator " + tokens[index].TokenValue);
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

            // Ensure there is an opening parenthesis to match
            if (operatorStack.empty()) {
                throw std::runtime_error("Mismatched parentheses: no matching '(' found");
            }

            // Pop and discard the opening parenthesis
            operatorStack.pop();
        }

        index++; // Move to the next token
    }

    // Process remaining operators
    while (!operatorStack.empty()) {
        if (expressionStack.size() < 2) {
            if (operatorStack.top().TokenType == Token::JagoTokenType::ParenthesisOpen) {
                throw std::runtime_error("Mismatched parentheses: no matching ')' found, found " + tokens[index].TokenValue);
            }

            throw std::runtime_error("Invalid state: insufficient expressions for remaining operators");
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