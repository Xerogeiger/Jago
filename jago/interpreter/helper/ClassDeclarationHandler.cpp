//
// Created by creep on 5/20/2025.
//

#include "ClassDeclarationHandler.h"

#include <assert.h>
#include <memory>

#include "../../exceptions/JagoCompilerException.h"
#include "../AST/StatementNodes.h"

namespace Jago {
    std::unique_ptr<ClassDeclarationStatement> ClassDeclarationHandler::handle(const JagoInterpreter& interpreter, std::vector<Jago::JagoToken> tokens, int &index) {
        if (tokens[index].TokenType != Token::JagoTokenType::Keyword) {
            throw JagoCompilerException("Expected class declaration to start with a keyword");
        }
        if (tokens[index].TokenValue != "class") {
            throw JagoCompilerException("Expected class declaration to start with 'class'");
        }

        index++;
        if (tokens[index].TokenType != Token::JagoTokenType::Name) {
            throw JagoCompilerException("Expected class name after 'class'");
        }

        auto className = tokens[index].TokenValue;
        index++;

        //TODO: Handle class inheritance
        if (tokens[index].TokenType != Token::JagoTokenType::ScopeOpen) {
            throw JagoCompilerException("Expected '{' after class name");
        }
        index++;
        std::vector<std::shared_ptr<JagoMethod>> classMethods;

        while (tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
            auto type = tokens[index].TokenValue; // The return type or variable type
            index++;
            if (tokens[index].TokenType != Token::JagoTokenType::Name) {
                throw JagoCompilerException("Expected variable name after type");
            }
            auto name = tokens[index].TokenValue;
            index++;

            std::vector<JagoParameter> parameters;

            assert(tokens[index].TokenType == Token::JagoTokenType::ParenthesisOpen);
            index++; // Skip the parenthesis open

            while (tokens[index].TokenType != Token::JagoTokenType::ParenthesisClose) {
                auto paramType = tokens[index].TokenValue; // The parameter type
                index++;
                if (tokens[index].TokenType != Token::JagoTokenType::Name) {
                    throw JagoCompilerException("Expected parameter name after type");
                }
                auto paramName = tokens[index].TokenValue;
                parameters.push_back(JagoParameter{ getTypeFromString(paramType), paramName });
                index++;
                if (tokens[index].TokenType == Token::JagoTokenType::Operator && tokens[index].TokenValue == ",") {
                    index++; // Skip the comma
                }
            }

            std::vector<std::unique_ptr<ASTNode>> methodBody;
            assert(tokens[index].TokenType == Token::JagoTokenType::ParenthesisClose);
            index++; // Skip the parenthesis close
            assert(tokens[index].TokenType == Token::JagoTokenType::ScopeOpen);
            index++; // Skip the scope open
            while (tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
                // Interpret statement or expression
                if (tokens[index].TokenType == Token::JagoTokenType::Keyword)
                    methodBody.push_back(interpreter.interpretStatement(tokens, index));
                else
                    methodBody.push_back(Jago::JagoInterpreter::interpretExpression(tokens, index));

                if (tokens[index].TokenType == Token::JagoTokenType::StatementEnd) {
                    index += 1;
                }
            }

            assert(tokens[index].TokenType == Token::JagoTokenType::ScopeClose);
            index++; // Skip the scope close

            std::shared_ptr<JagoMethod> method = std::make_shared<JagoMethod>(name, std::make_unique<ScopeBody>(std::move(methodBody)), parameters);

            classMethods.push_back(
                method
            );
        }

        assert(tokens[index].TokenType == Token::JagoTokenType::ScopeClose);
        index++; // Skip the scope close

        return std::make_unique<ClassDeclarationStatement>(className, std::move(classMethods));
    }
}