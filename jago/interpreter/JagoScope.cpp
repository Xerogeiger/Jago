//
// Created by creep on 1/12/2025.
//

#include "JagoScope.h"
#include <string_view>
#include <utility>
#include <iostream>

namespace Jago {
    Jago::JagoValue JagoScope::getVariable(const std::string_view name) {
        if (variables.contains(name))
            return variables[name];
        if (parentScope != nullptr)
            return parentScope->getVariable(name);

        return JagoValue(PrimitiveTypes::VOID, static_cast<void*>(nullptr));
    }

    Jago::JagoMethod JagoScope::getFunction(const std::string_view name) {
        if (functions.contains(name))
            return functions[name];
        if (parentScope != nullptr)
            return parentScope->getFunction(name);

        return {};
    }

    void JagoScope::setVariable(std::string_view name, Jago::JagoValue value) {
        variables.insert_or_assign(name, std::move(value));
    }

    void JagoScope::setFunction(std::string_view name, Jago::JagoMethod method) {
        functions.insert_or_assign(name, std::move(method));
    }

    void JagoScope::dump(std::ostream &out) {
        for (const auto& [name, value] : variables) {
            out << "Variable: " << name << " = " << value << std::endl;
        }

        for (const auto& [name, method] : functions) {
            out << "Function: " << name << std::endl;
        }
    }
} // Jago