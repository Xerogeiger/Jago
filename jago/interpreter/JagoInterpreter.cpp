//
// Created by creep on 1/12/2025.
//

#include "JagoInterpreter.h"

#include <assert.h>
#include <stack>

#include "../JagoGlobal.h"
#include "../exceptions/JagoCompilerException.h"
#include "AST/ASTNode.h"
#include "AST/StatementNodes.h"
#include "JagoMethod.h"
#include "helper/ClassDeclarationHandler.h"

namespace Jago {
    ASTNode* JagoInterpreter::interpret(const std::vector<Jago::JagoToken> tokens) const {
        auto program = new Program();

        int index = 0;
        while (index < tokens.size()) {

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

    int findClosingParen(const std::vector<JagoToken>& tokens, int openPos) {
        int depth = 1;
        for (int i = openPos + 1; i < (int)tokens.size(); ++i) {
            if (tokens[i].TokenType == Token::JagoTokenType::ParenthesisOpen)  ++depth;
            else if (tokens[i].TokenType == Token::JagoTokenType::ParenthesisClose) {
                if (--depth == 0) return i;
            }
        }
        throw JagoCompilerException("Missing closing parenthesis for method call");
    }

    std::unique_ptr<Statement> JagoInterpreter::interpretStatement(std::vector<Jago::JagoToken> tokens,
        int &index) const {
        std::cout << "Processing statement token: " << tokens[index] << std::endl;
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
                        if (tokens[index].TokenValue == ",")
                            index++;
                    }

                    index += 1; // Skip the parenthesis close
                }

                if (tokens[index].TokenType == Token::JagoTokenType::ScopeOpen) {
                    index += 1; // Skip the scope open
                    std::vector<std::unique_ptr<ASTNode>> statements;
                    while (tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
                        std::cout << "Processing scope body token: " << tokens[index] << std::endl;
                        // Interpret statement or expression
                        if (tokens[index].TokenType == Token::JagoTokenType::Keyword)
                            statements.push_back(interpretStatement(tokens, index));
                        else
                            statements.push_back(interpretExpression(tokens, index));

                        if (tokens[index].TokenType == Token::JagoTokenType::StatementEnd) {
                            index += 1;
                        }
                    }

                    index += 1; // Skip the scope close

                    return std::make_unique<MethodDeclarationStatement>(methodName, getTypeFromString(returnType), parameters, std::make_unique<ScopeBody>(std::move(statements)));
                } else {
                    throw Jago::JagoCompilerException("Method declaration is missing a scope");
                }
            } else if (tokens[index].TokenValue == "if") {
                if (tokens[++index].TokenType == Token::JagoTokenType::ParenthesisOpen) {
                    int closingParenthesis = findClosingParen(tokens, index);

                    index++; // Skip the parenthesis open

                    auto condition = interpretExpression(tokens, index, closingParenthesis);

                    assert(tokens[index].TokenType == Token::JagoTokenType::ParenthesisClose);
                    index++; // Skip the parenthesis close

                    std::unique_ptr<ASTNode> trueCase;
                    std::unique_ptr<ASTNode> falseCase = nullptr;

                    if (tokens[index].TokenType == Token::JagoTokenType::ScopeOpen) {
                        index += 1; // Skip the scope open
                        std::vector<std::unique_ptr<ASTNode>> statements;
                        while (tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
                            // Interpret statement or expression
                            if (tokens[index].TokenType == Token::JagoTokenType::Keyword)
                                statements.push_back(interpretStatement(tokens, index));
                            else
                                statements.push_back(interpretExpression(tokens, index));

                            if (tokens[index].TokenType == Token::JagoTokenType::StatementEnd) {
                                index += 1;
                            }
                        }

                        index += 1; // Skip the scope close

                        trueCase = std::make_unique<ScopeBody>(std::move(statements));
                    } else {
                        if (tokens[index].TokenType == Token::JagoTokenType::Keyword)
                            trueCase = interpretStatement(tokens, index);
                        else
                            trueCase = interpretExpression(tokens, index);
                        assert(tokens[index].TokenType == Token::JagoTokenType::StatementEnd);
                        index += 1; // Skip the statement end
                    }
                    if (tokens[index].TokenValue == "else") {
                        index += 1; // Skip the else keyword
                        if (tokens[index].TokenType == Token::JagoTokenType::ScopeOpen) {
                            index += 1; // Skip the scope open
                            std::vector<std::unique_ptr<ASTNode>> statements;
                            while (tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
                                // Interpret statement or expression
                                if (tokens[index].TokenType == Token::JagoTokenType::Keyword)
                                    statements.push_back(interpretStatement(tokens, index));
                                else
                                    statements.push_back(interpretExpression(tokens, index));

                                if (tokens[index].TokenType == Token::JagoTokenType::StatementEnd) {
                                    index += 1;
                                }
                            }

                            index += 1; // Skip the scope close

                            falseCase = std::make_unique<ScopeBody>(std::move(statements));
                        } else if (tokens[index].TokenValue == "if") {
                            falseCase = interpretStatement(tokens, index); // Interpret the else if statement
                            assert(tokens[index].TokenType == Token::JagoTokenType::StatementEnd);
                            index += 1; // Skip the statement end
                        }
                    }

                    return std::make_unique<IfStatement>(std::move(trueCase), std::move(falseCase), std::move(condition));
                } else {
                    throw Jago::JagoCompilerException("Missing opening parenthesis for if statement");
                }
            } else if (tokens[index].TokenValue == "for") {
                index += 1; // Skip the for keyword
                assert(tokens[index].TokenType == Token::JagoTokenType::ParenthesisOpen);
                int closingParenthesis = findClosingParen(tokens, index);
                index += 1; // Skip the parenthesis open
                auto initStatement = interpretStatement(tokens, index); // Initialization statement
                assert(tokens[index].TokenType == Token::JagoTokenType::StatementEnd);
                index += 1; // Skip the semicolon
                auto condition = interpretExpression(tokens, index); // Condition expression
                assert(tokens[index].TokenType == Token::JagoTokenType::StatementEnd);
                index += 1; // Skip the semicolon
                auto increment = interpretExpression(tokens, index, closingParenthesis); // Increment expression
                assert(tokens[index].TokenType == Token::JagoTokenType::ParenthesisClose);
                index += 1; // Skip the parenthesis close
                assert(tokens[index].TokenType == Token::JagoTokenType::ScopeOpen);
                index += 1; // Skip the scope open
                std::vector<std::unique_ptr<ASTNode>> statements;
                while (tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
                    // Interpret statement or expression
                    if (tokens[index].TokenType == Token::JagoTokenType::Keyword)
                        statements.push_back(interpretStatement(tokens, index));
                    else
                        statements.push_back(interpretExpression(tokens, index));

                    if (tokens[index].TokenType == Token::JagoTokenType::StatementEnd) {
                        index += 1;
                    }
                }
                index += 1; // Skip the scope close
                return std::make_unique<IncrementalForStatement>(std::move(initStatement), std::move(condition), std::move(increment), std::make_unique<ScopeBody>(std::move(statements)));
            } else if (tokens[index].TokenValue == "continue") {
                index += 1; // Skip the continue keyword
                assert(tokens[index].TokenType == Token::JagoTokenType::StatementEnd);
                return std::make_unique<ContinueStatement>();
            } else if (tokens[index].TokenValue == "class") {
                return ClassHandler.handle(*this, tokens, index);
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

        throw Jago::JagoCompilerException("Invalid statement, statement must start with a keyword");
        return nullptr;
    }

    int nextIndexOf(std::vector<Jago::JagoToken> tokens, int startIndex, std::string token, uint32_t len) {
        for (int i = startIndex; i < len; ++i) {
            if (tokens[i].TokenValue == token) {
                return i;
            }
        }
        return -1; // Not found
    }

std::unique_ptr<Expression>
JagoInterpreter::interpretExpression(const std::vector<JagoToken>& tokens,
                                     int& index,
                                     uint32_t len) {
    // If caller passed -1, use the full token list
    if (len == static_cast<uint32_t>(-1))
        len = tokens.size();

    std::stack<JagoToken>                   operatorStack;
    std::stack<std::unique_ptr<Expression>> expressionStack;

    // ----------------------------------------------------------------
    // 1) Precedence and associativity lookups
    // ----------------------------------------------------------------
    enum class Assoc { Left, Right };

    auto precedence = [&](const std::string &opStr) -> int {
        for (auto &op : Jago::DefaultJagoOperators) {
            if (op.OperatorSymbol == opStr)
                return op.Precedence;
        }
        throw std::runtime_error("Unknown operator: " + opStr);
    };

    auto getAssociativity = [&](const std::string &opStr) -> Assoc {
        for (auto &op : Jago::DefaultJagoOperators) {
            if (op.OperatorSymbol == opStr) {
                switch (op.OperatorType) {
                    // make all assignments & exponentiation right-assoc
                    case Operator::OperatorType::Assignment:
                    case Operator::OperatorType::AdditionAssignment:
                    case Operator::OperatorType::SubtractionAssignment:
                    case Operator::OperatorType::MultiplicationAssigment:
                    case Operator::OperatorType::DivisionAssignment:
                    case Operator::OperatorType::ModulusAssignment:
                    case Operator::OperatorType::PowerOfAssignment:
                    case Operator::OperatorType::PowerOf:
                        return Assoc::Right;
                    default:
                        return Assoc::Left;
                }
            }
        }
        return Assoc::Left;  // fallback
    };

    // ----------------------------------------------------------------
    // 2) Pop one operator off and build a BinaryExpression
    // ----------------------------------------------------------------
    auto popAndBuildBinary = [&]() {
        if (expressionStack.size() < 2)
            throw std::runtime_error("Invalid state: insufficient expressions to apply operator");

        auto right = std::move(expressionStack.top()); expressionStack.pop();
        auto left  = std::move(expressionStack.top()); expressionStack.pop();
        auto opTok = operatorStack.top(); operatorStack.pop();

        expressionStack.push(
            std::make_unique<BinaryExpression>(
                std::move(left),
                std::move(right),
                opTok.TokenValue
            )
        );
    };

    // ----------------------------------------------------------------
    // 3) Shunting‐yard / main loop
    // ----------------------------------------------------------------
    while (index < len
        && tokens[index].TokenType != Token::JagoTokenType::StatementEnd
        && tokens[index].TokenType != Token::JagoTokenType::ScopeClose) {
        const auto &tok = tokens[index];

        if (tok.TokenType == Token::JagoTokenType::Name && tok.TokenValue == "new") {
            index++;
            if (tokens[index].TokenType != Token::JagoTokenType::Name)
                throw JagoCompilerException("Expected class name after 'new'");
            auto className = tokens[index].TokenValue;
            index++;

            assert(tokens[index].TokenType == Token::JagoTokenType::ParenthesisOpen);
            int closingParen = findClosingParen(tokens, index);
            index++; // Skip the parenthesis open
            std::vector<std::unique_ptr<Expression>> args;
            while (index < closingParen) {
                int nextComma = nextIndexOf(tokens, index, ",", closingParen);
                int subEnd    = nextComma >= 0 ? nextComma : closingParen;

                args.push_back(interpretExpression(tokens, index, subEnd-1));

                if (index < len && tokens[index].TokenValue == ",")
                    ++index;  // skip comma
            }

            assert(tokens[index].TokenType == Token::JagoTokenType::ParenthesisClose);
            index++; // Skip the parenthesis close

            expressionStack.push(std::make_unique<NewExpression>(
                className,
                std::move(args)
            ));
            continue;
        }

        // --- 3.1 Literals ---
        if (tok.TokenType == Token::JagoTokenType::NumberLiteral ||
            tok.TokenType == Token::JagoTokenType::StringLiteral ||
            tok.TokenType == Token::JagoTokenType::CharacterLiteral)
        {
            expressionStack.push(std::make_unique<Literal>(tok.TokenValue));
            ++index;
            continue;
        }

        // --- 3.2 Variables & Method Calls ---
        if (tok.TokenType == Token::JagoTokenType::Name) {
            // method call?
            if (index + 1 < len
                && tokens[index+1].TokenType == Token::JagoTokenType::ParenthesisOpen)
            {
                std::string methodName = tok.TokenValue;
                int openIdx  = index+1;
                int closeIdx = findClosingParen(tokens, openIdx);
                if (closeIdx < 0)
                    throw Jago::JagoCompilerException("Missing ')' after method call");

                index = openIdx + 1;  // skip name + '('
                std::vector<std::unique_ptr<Expression>> args;

                while (index < closeIdx) {
                    int nextComma = nextIndexOf(tokens, index, ",", closeIdx);
                    int subEnd    = nextComma >= 0 ? nextComma : closeIdx;

                    args.push_back(interpretExpression(tokens, index, subEnd));

                    if (index < len && tokens[index].TokenValue == ",")
                        ++index;  // skip comma
                }

                index = closeIdx + 1; // skip ')'
                expressionStack.push(
                    std::make_unique<MethodCallExpression>(methodName, std::move(args))
                );
            }
            else {
                // simple variable
                expressionStack.push(
                    std::make_unique<Variable>(tok.TokenValue)
                );
                ++index;
            }
            continue;
        }

        // --- 3.3 Operators ---
        if (tok.TokenType == Token::JagoTokenType::Operator) {
            std::string curOp    = tok.TokenValue;
            int         curPrec  = precedence(curOp);
            Assoc       curAssoc = getAssociativity(curOp);

            auto shouldPop = [&](const std::string &stackOp) {
                int stackPrec = precedence(stackOp);
                if (stackPrec > curPrec) return true;
                if (stackPrec == curPrec && curAssoc == Assoc::Left) return true;
                return false;
            };

            // pop all tighter (or equal+left-assoc)
            while (!operatorStack.empty()
                   && operatorStack.top().TokenType != Token::JagoTokenType::ParenthesisOpen
                   && shouldPop(operatorStack.top().TokenValue))
            {
                popAndBuildBinary();
            }

            operatorStack.push(tok);
            ++index;
            continue;
        }

        // --- 3.4 Parentheses ---
        if (tok.TokenType == Token::JagoTokenType::ParenthesisOpen) {
            operatorStack.push(tok);
            ++index;
            continue;
        }
        if (tok.TokenType == Token::JagoTokenType::ParenthesisClose) {
            // pop until '('
            while (!operatorStack.empty()
                   && operatorStack.top().TokenType != Token::JagoTokenType::ParenthesisOpen)
            {
                popAndBuildBinary();
            }
            if (operatorStack.empty())
                throw std::runtime_error("Mismatched parentheses");
            operatorStack.pop();  // drop '('
            ++index;
            continue;
        }

        // --- 3.5 Anything else (commas, semicolons you didn’t explicitly handle) ---
        ++index;
    }

    // ----------------------------------------------------------------
    // 4) Drain any remaining operators
    // ----------------------------------------------------------------
    while (!operatorStack.empty()) {
        if (operatorStack.top().TokenType == Token::JagoTokenType::ParenthesisOpen)
            throw std::runtime_error("Mismatched parentheses");
        popAndBuildBinary();
    }

    // ----------------------------------------------------------------
    // 5) Final sanity check
    // ----------------------------------------------------------------
    if (expressionStack.size() != 1)
        throw std::runtime_error("Invalid expression: unexpected stack size " +
                                 std::to_string(expressionStack.size()));

    return std::move(expressionStack.top());
}


} // Jago