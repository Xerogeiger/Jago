//
// Created by creep on 12/14/2022.
//

#include "JagoCompiler.h"

Jago::JagoCompiler::JagoCompiler() {
    this->settings = CompilerSettings {
            .Operators = DefaultJagoOperators,
            .Keywords = DefaultJagoKeywords
    };

    this->operatorMap.clear();

    for(const auto& op: settings.Operators) {
        this->operatorMap[op.OperatorUsage][op.OperatorSymbol] = op;
    }
}

struct CompiledVariable {
    int variableIndex;
    std::string_view name;
    Jago::JagoType type;
};

struct Expression {
    uint64_t expressionStart;
    uint64_t expressionEnd;
} NullExpression{0, 0};

union Byte {
    uint8_t bytes;

    uint8_t charValue;
    int8_t byteValue;
} ByteConverter;

union Word {
    uint8_t bytes[2];

    uint16_t unsignedShortValue;

    uint16_t wideCharValue;
    int16_t shortValue;
} WordConverter;

union DoubleWord {
    uint8_t bytes[4];

    uint32_t unsignedIntValue;
    int32_t intValue;

    float floatValue;
} DoubleWordConverter;

union QuadrupleWord {
    uint8_t bytes[8];

    uint64_t unsignedLongValue;
    int64_t longValue;

    double doubleValue;
} QuadrupleWordConverter;

void ExpectNextToken(std::vector<Jago::JagoToken>::iterator cur, std::vector<Jago::JagoToken>::iterator end, const char* message) {
    if(++cur == end)
        throw Jago::JagoCompilerException(message);
}

Jago::JagoType GetTypeByName(std::string& typeName) {
    if(Jago::StringEquals(typeName, "int")) {
        return Jago::INT;
    } else if(Jago::StringEquals(typeName, "long")) {
        return Jago::LONG;
    } else if(Jago::StringEquals(typeName, "byte")) {
        return Jago::BYTE;
    } else if(Jago::StringEquals(typeName, "short")) {
        return Jago::SHORT;
    } else if(Jago::StringEquals(typeName, "float")) {
        return Jago::FLOAT;
    } else if(Jago::StringEquals(typeName, "double")) {
        return Jago::DOUBLE;
    } else if(Jago::StringEquals(typeName, "char")) {
        return Jago::CHAR;
    } else {
        return Jago::OBJECT;
    }
}

void AddLongToByteCode(std::vector<uint8_t>& byteCode, long value) {
    QuadrupleWordConverter.longValue = value;

    byteCode.push_back(QuadrupleWordConverter.bytes[0]);
    byteCode.push_back(QuadrupleWordConverter.bytes[1]);
    byteCode.push_back(QuadrupleWordConverter.bytes[2]);
    byteCode.push_back(QuadrupleWordConverter.bytes[3]);
    byteCode.push_back(QuadrupleWordConverter.bytes[4]);
    byteCode.push_back(QuadrupleWordConverter.bytes[5]);
    byteCode.push_back(QuadrupleWordConverter.bytes[6]);
    byteCode.push_back(QuadrupleWordConverter.bytes[7]);
}

void AddStringToByteCode(std::vector<uint8_t>& byteCode, std::string_view value) {
    AddLongToByteCode(byteCode, (long) value.length());

    for(char itr : value) {
        byteCode.push_back(itr);
    }
}

void AddIntToByteCode(std::vector<uint8_t>& byteCode, int value) {
    DoubleWordConverter.intValue = value;

    byteCode.push_back(DoubleWordConverter.bytes[0]);
    byteCode.push_back(DoubleWordConverter.bytes[1]);
    byteCode.push_back(DoubleWordConverter.bytes[2]);
    byteCode.push_back(DoubleWordConverter.bytes[3]);
}

void AddShortToByteCode(std::vector<uint8_t>& byteCode, short value) {
    WordConverter.shortValue = value;

    byteCode.push_back(WordConverter.bytes[0]);
    byteCode.push_back(WordConverter.bytes[1]);
}

void AddFloatToByteCode(std::vector<uint8_t>& byteCode, float value) {
    DoubleWordConverter.floatValue = value;

    byteCode.push_back(DoubleWordConverter.bytes[0]);
    byteCode.push_back(DoubleWordConverter.bytes[1]);
    byteCode.push_back(DoubleWordConverter.bytes[2]);
    byteCode.push_back(DoubleWordConverter.bytes[3]);
}

void AddDoubleToByteCode(std::vector<uint8_t>& byteCode, double value) {
    QuadrupleWordConverter.doubleValue = value;

    byteCode.push_back(QuadrupleWordConverter.bytes[0]);
    byteCode.push_back(QuadrupleWordConverter.bytes[1]);
    byteCode.push_back(QuadrupleWordConverter.bytes[2]);
    byteCode.push_back(QuadrupleWordConverter.bytes[3]);
    byteCode.push_back(QuadrupleWordConverter.bytes[4]);
    byteCode.push_back(QuadrupleWordConverter.bytes[5]);
    byteCode.push_back(QuadrupleWordConverter.bytes[6]);
    byteCode.push_back(QuadrupleWordConverter.bytes[7]);
}

std::vector<uint8_t> Jago::JagoCompiler::Compile(std::vector<Jago::JagoToken> tokens) {
    std::vector<uint8_t> compiledCode;

    std::unordered_map<std::string_view, CompiledVariable> globalVariables;
    std::vector<Expression> expressions;

    int globalVariableCounter = 0;

    Expression currentExpression = NullExpression;

    for(auto itr = tokens.begin(); itr != tokens.end(); itr++) { //Collect global variables, methods, and types
        if(itr->TokenType == Token::JagoTokenType::StatementEnd) continue;

        if(currentExpression.expressionStart != 0)
            currentExpression.expressionStart = itr - tokens.begin();

        if(itr->TokenType == Token::JagoTokenType::Name) {
            Jago::JagoToken firstToken = *itr;
            ExpectNextToken(itr, tokens.end(), "Invalid Expression");
            if(itr->TokenType == Token::JagoTokenType::Name) { //A Name followed by another name is a variable, 'int' and 'foo' in 'int foo = 3;' is a variable declaration
                if(globalVariables.contains(itr->TokenValue)) {
                    throw Jago::JagoCompilerException("Variable is already defined");
                }

                globalVariables[itr->TokenValue] = CompiledVariable{ .variableIndex = globalVariableCounter++,
                                                                     .name = itr->TokenValue,
                                                                     .type = GetTypeByName(firstToken.TokenValue) };

                currentExpression.expressionStart = itr - tokens.begin();

                for(; itr != tokens.end(); itr++) { //Collect global variables, methods, and types
                    if(itr->TokenType == Token::JagoTokenType::StatementEnd) {
                        break;
                    }
                }

                if(itr == tokens.end()) {
                    throw JagoCompilerException("Expression is missing a semicolon at the end");
                } else {
                    if(currentExpression.expressionStart != 0) {
                        currentExpression.expressionEnd = itr - tokens.begin();
                        expressions.push_back(currentExpression);
                    }
                    currentExpression = NullExpression;
                }
            }
        } else {
            for(; itr != tokens.end(); itr++) { //Collect global variables, methods, and types
                if(itr->TokenType == Token::JagoTokenType::StatementEnd) {
                    break;
                }
            }

            if(itr == tokens.end()) {
                throw JagoCompilerException("Expression is missing a semicolon at the end");
            } else {
                if(currentExpression.expressionStart != 0) {
                    currentExpression.expressionEnd = itr - tokens.begin();
                    expressions.push_back(currentExpression);
                }
                currentExpression = NullExpression;
            }
        }
    }

    for(auto & globalVariable : globalVariables) {
        switch (globalVariable.second.type) {
            case JagoType::BYTE:
                compiledCode.push_back(Jago::ByteCode::DEFINE_VARIABLE_8);
                AddStringToByteCode(compiledCode, globalVariable.second.name);
                AddIntToByteCode(compiledCode, globalVariable.second.variableIndex);
                break;
            case JagoType::SHORT:
                compiledCode.push_back(Jago::ByteCode::DEFINE_VARIABLE_16);
                AddStringToByteCode(compiledCode, globalVariable.second.name);
                AddIntToByteCode(compiledCode, globalVariable.second.variableIndex);
                break;
            case JagoType::INT:
                compiledCode.push_back(Jago::ByteCode::DEFINE_VARIABLE_32);
                AddStringToByteCode(compiledCode, globalVariable.second.name);
                AddIntToByteCode(compiledCode, globalVariable.second.variableIndex);
                break;
            case JagoType::LONG:
                compiledCode.push_back(Jago::ByteCode::DEFINE_VARIABLE_64);
                AddStringToByteCode(compiledCode, globalVariable.second.name);
                AddIntToByteCode(compiledCode, globalVariable.second.variableIndex);
                break;
            case JagoType::FLOAT:
                compiledCode.push_back(Jago::ByteCode::DEFINE_VARIABLE_32);
                AddStringToByteCode(compiledCode, globalVariable.second.name);
                AddIntToByteCode(compiledCode, globalVariable.second.variableIndex);
                break;
            case JagoType::DOUBLE:
                compiledCode.push_back(Jago::ByteCode::DEFINE_VARIABLE_64);
                AddStringToByteCode(compiledCode, globalVariable.second.name);
                AddIntToByteCode(compiledCode, globalVariable.second.variableIndex);
                break;
            default:
                throw JagoCompilerException("Provided variable width isn't valid");
        }
    }

    for(auto& expression: expressions) {
        std::stack<Jago::Operator::JagoOperator> operatorStack;
        std::vector<Jago::JagoToken> result;

        for(uint64_t i = expression.expressionStart; i < expression.expressionEnd; i++) {
            auto& token = tokens[i];

            if (token.TokenType == Token::JagoTokenType::Operator) {
                bool valueOnRight = true;
                bool valueOnLeft = true;

                if(expression.expressionEnd == i+1 || tokens[i+1].TokenType == Token::JagoTokenType::Operator) {
                    valueOnRight = false;
                }

                if(i != 0 && tokens[i-1].TokenType == Token::JagoTokenType::Operator) {
                    valueOnLeft = false;
                }

                if(!(valueOnRight || valueOnLeft))
                    throw std::invalid_argument("Operator is surrounded by two other operators on line " + std::to_string(token.LineNumber));

                Operator::JagoOperator op = this->operatorMap[valueOnLeft && valueOnRight ? Operator::OperatorUsage::Binary : (valueOnLeft ? Operator::OperatorUsage::LeftSideUnary : Operator::OperatorUsage::RightSideUnary)][token.TokenValue];

                while (!operatorStack.empty()
                       && op.Precedence <= operatorStack.top().Precedence) {
                    result.push_back(Jago::JagoToken{.TokenType = Token::JagoTokenType::Operator, .TokenValue = operatorStack.top().OperatorSymbol, .LineNumber = -1});
                    operatorStack.pop();
                }
                operatorStack.push(op);
            } else if (token.TokenType == Token::JagoTokenType::ParenthesisOpen) {
                operatorStack.push(Jago::ParenthesisOpenOperator);
            } else if (token.TokenType == Token::JagoTokenType::ParenthesisClose) {
                while (operatorStack.top().OperatorType != Jago::Operator::ParenthesisClose) {
                    result.push_back(Jago::JagoToken{.TokenType = Token::JagoTokenType::Operator, .TokenValue = operatorStack.top().OperatorSymbol, .LineNumber = -1});
                    operatorStack.pop();
                }
                operatorStack.pop();
            } else {
                result.push_back(token);
            }
        }

        while (!operatorStack.empty()) {
            result.push_back(Jago::JagoToken{.TokenType = Token::JagoTokenType::Operator, .TokenValue = operatorStack.top().OperatorSymbol, .LineNumber = -1});
            operatorStack.pop();
        }
    }

    return compiledCode;
}
