//
// Created by creep on 1/12/2025.
//

#ifndef JAGOSCOPE_H
#define JAGOSCOPE_H
#include <map>
#include <string>

#include "JagoMethod.h"

namespace Jago {
    class JagoScope {
    protected:
        JagoScope* parentScope = nullptr;

        std::map<std::string_view, Jago::JagoMethod> functions;
        std::map<std::string_view, Jago::JagoValue> variables;

    public:
        [[nodiscard]] Jago::JagoValue getVariable(std::string_view name);
        [[nodiscard]] Jago::JagoMethod getFunction(std::string_view name);

        void setVariable(std::string_view name, Jago::JagoValue value);

        void setFunction(std::string_view name, Jago::JagoMethod method);

        void dump(std::ostream & out);
    };

} // Jago

#endif //JAGOSCOPE_H
