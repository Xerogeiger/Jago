//
// Created by creep on 12/14/2022.
//

#ifndef JAGO_JAGOMETHOD_H
#define JAGO_JAGOMETHOD_H

#include <vector>
#include <string>
#include "JagoType.fwd.h"
#include "JagoVariable.h"

namespace Jago {
    class JagoMethod {
    private:
        std::string methodName;
        JagoType* returnType;
        std::vector<JagoType*> methodArguments;
    public:
        JagoMethod(const std::string& name, JagoType* returnType, const std::vector<JagoType*>& argumentTypes);

        virtual JagoVariable* Invoke(JagoVariable* arguments, int argumentLength) = 0;
        [[nodiscard]] std::string GetMethodName() const;
        [[nodiscard]] JagoType* GetReturnType() const;
        [[nodiscard]] std::vector<JagoType*> GetMethodArguments() const;
    };
}


#endif //JAGO_JAGOMETHOD_H
