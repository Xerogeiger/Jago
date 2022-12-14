//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOINTERPRETER_H
#define JAGO_JAGOINTERPRETER_H

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <stack>
#include "../JagoUtils.h"
#include "../JagoToken.h"
#include "JagoScope.h"
#include "../JagoOperator.h"
#include "../JagoKeyword.h"
#include "../JagoGlobal.h"
#include "JagoType.h"
#include "JagoMethod.h"
#include "JagoField.h"
#include "JagoVariable.h"

namespace Jago {
    struct InterpreterSettings {
        std::vector<JagoOperator> Operators;
        std::vector<const JagoKeyword*> Keywords;
        JagoType* intType;
    };

    class JagoInterpreter {
    protected:
        std::unordered_map<OperatorUsage, std::unordered_map<std::string, JagoOperator>> operatorMap;
        InterpreterSettings settings;

        JagoScope *globalScope;
        JagoScope *currentScope;
    public:
        JagoInterpreter();

        void Interpret(std::vector<Jago::JagoToken> tokens);

    private:
        void InterpretVariable(Jago::JagoVariable* variable, std::vector<Jago::JagoToken>::iterator& current, std::vector<Jago::JagoToken>::iterator end);
        void HandleVariableOrMethod(std::vector<Jago::JagoToken>::iterator& current, std::vector<Jago::JagoToken>::iterator end);
    };
}

#endif //JAGO_JAGOINTERPRETER_H
