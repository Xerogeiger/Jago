//
// Created by creep on 12/14/2022.
//

#ifndef JAGO_JAGOCOMPILER_H
#define JAGO_JAGOCOMPILER_H

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <stack>
#include "../JagoUtils.h"
#include "../JagoToken.h"
#include "../JagoOperator.h"
#include "../JagoKeyword.h"
#include "../JagoGlobal.h"
#include "../JagoBytecodes.h"
#include "../exceptions/JagoCompilerException.h"
#include "JagoType.h"

namespace Jago {
    struct CompilerSettings {
        std::vector<Operator::JagoOperator> Operators;
        std::vector<const JagoKeyword*> Keywords;
    };

    class JagoCompiler {
    protected:
        std::unordered_map <Operator::OperatorUsage, std::unordered_map<std::string, Operator::JagoOperator>> operatorMap;
        CompilerSettings settings;
    public:
        JagoCompiler();

        std::vector<uint8_t> Compile(std::vector <Jago::JagoToken> tokens);
    };
}


#endif //JAGO_JAGOCOMPILER_H
