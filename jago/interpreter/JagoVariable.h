//
// Created by creep on 12/14/2022.
//

#ifndef JAGO_JAGOVARIABLE_H
#define JAGO_JAGOVARIABLE_H

#include <cstdint>
#include <string>
#include "JagoType.fwd.h"

namespace Jago {
    class JagoVariable {
    protected:
        std::string variableName;
        JagoType* variableType;
        uint64_t variableValue;
    public:
        JagoVariable(const std::string& name, JagoType* variableType);
        JagoVariable(const std::string& name, JagoType* variableType, uint64_t value);

        template <typename T>
        T GetValue();

        template <typename T>
        void SetValue(T value);
    };
}

#endif //JAGO_JAGOVARIABLE_H
