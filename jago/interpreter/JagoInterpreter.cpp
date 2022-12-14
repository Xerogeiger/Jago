//
// Created by creep on 12/13/2022.
//

#include "JagoInterpreter.h"

void Jago::JagoInterpreter::InterpretVariable(Jago::JagoVariable* variable, std::vector<Jago::JagoToken>::iterator& current, std::vector<Jago::JagoToken>::iterator end) {
    std::vector<Jago::JagoToken> statementTokens;

    for(; current != end; current++) {
        if(current->TokenType == Jago::JagoTokenType::StatementEnd)
            break;
        else
            statementTokens.push_back(*current);
    }

    PrintArray(statementTokens);

    std::stack<JagoOperator> operatorStack;

    std::vector<Jago::JagoToken> result;

    for (int i = 0; i < statementTokens.size(); i++) {
        Jago::JagoToken token = statementTokens[i];

        if (token.TokenType == Jago::JagoTokenType::Operator) {
            bool valueOnRight = true;
            bool valueOnLeft = true;

            if(statementTokens.size() == i+1 || statementTokens[i+1].TokenType == Jago::JagoTokenType::Operator) {
                valueOnRight = false;
            }

            if(i != 0 && statementTokens[i-1].TokenType == Jago::JagoTokenType::Operator) {
                valueOnLeft = false;
            }

            if(!(valueOnRight || valueOnLeft))
                throw std::invalid_argument("Operator is surrounded by two other operators on line " + std::to_string(token.LineNumber));

            JagoOperator op = this->operatorMap[valueOnLeft && valueOnRight ? OperatorUsage::Binary : (valueOnLeft ? OperatorUsage::LeftSideUnary : OperatorUsage::RightSideUnary)][token.TokenValue];

            while (!operatorStack.empty()
                   && op.Precedence <= operatorStack.top().Precedence) {
                result.push_back(Jago::JagoToken{.TokenType = Jago::JagoTokenType::Operator, .TokenValue = operatorStack.top().OperatorSymbol, .LineNumber = -1});
                operatorStack.pop();
            }
            operatorStack.push(op);
        } else if (token.TokenType == Jago::JagoTokenType::ParenthesisOpen) {
            operatorStack.push(Jago::ParenthesisOpenOperator);
        } else if (token.TokenType == Jago::JagoTokenType::ParenthesisClose) {
            while (operatorStack.top().OperatorType != OperatorType::ParenthesisOpen) {
                result.push_back(Jago::JagoToken{.TokenType = Jago::JagoTokenType::Operator, .TokenValue = operatorStack.top().OperatorSymbol, .LineNumber = -1});
                operatorStack.pop();
            }
            operatorStack.pop();
        } else {
            result.push_back(token);
        }
    }

    while (!operatorStack.empty()) {
        result.push_back(Jago::JagoToken{.TokenType = Jago::JagoTokenType::Operator, .TokenValue = operatorStack.top().OperatorSymbol, .LineNumber = -1});
        operatorStack.pop();
    }

    PrintArray(result);
}

void Jago::JagoInterpreter::HandleVariableOrMethod(std::vector<Jago::JagoToken>::iterator& current, std::vector<Jago::JagoToken>::iterator end) {
    auto token = *current;

    if(this->currentScope->ContainsType(token.TokenValue)) { //If this is a type it is either a variable or method declaration
        auto declaredType = this->currentScope->GetType(token.TokenValue);

        if(++current == end)
            throw std::invalid_argument("Expected declared variable or method name but hit the end of the file instead on line " + std::to_string(token.LineNumber));

        auto nameToken = *current;

        if(nameToken.TokenType != JagoTokenType::Name) {
            throw std::invalid_argument(std::string("Expected declared variable or method name but got a token of type ") +
            JagoTokenTypeNames[nameToken.TokenType] + " instead to line " + std::to_string(nameToken.LineNumber));
        }

        if(++current == end)
            throw std::invalid_argument("Expected declared variable or method name but hit the end of the file instead on line " + std::to_string(token.LineNumber));

        auto declarationTypeToken = *current;

        if(declarationTypeToken.TokenType == JagoTokenType::Operator) { //An operator always means that it is a variable
            auto* newVariable = new JagoVariable(nameToken.TokenValue, declaredType);
            InterpretVariable(newVariable, current, end);
            this->currentScope->AddVariable(nameToken.TokenValue, newVariable);
        }
    }
}

void Jago::JagoInterpreter::Interpret(std::vector<Jago::JagoToken> tokens) {
    JagoType* memberType;

    for(auto itr = tokens.begin(); itr != tokens.end(); itr++) {
        auto token = *itr;

        if(token.TokenType == JagoTokenType::Name) { //If the first value is a name it is either a variable or method
            HandleVariableOrMethod(itr, tokens.end());
        }
    }
}

Jago::JagoInterpreter::JagoInterpreter() {
    this->globalScope = new Jago::JagoScope();
    this->currentScope = globalScope;

    auto intType = new Jago::JagoType("int");

    this->globalScope->AddType("int", intType);

    this->settings = InterpreterSettings {
        .Operators = DefaultJagoOperators,
        .Keywords = DefaultJagoKeywords,
        .intType = intType
    };

    this->operatorMap.clear();

    for(const auto& op: settings.Operators) {
        this->operatorMap[op.OperatorUsage][op.OperatorSymbol] = op;
    }
}
