//
// Created by creep on 1/12/2025.
//

#include "JagoScope.h"
#include <string_view>
#include <utility>
#include <iostream>

#include "JagoMethod.h"

namespace Jago {
    Jago::JagoValue JagoScope::getVariable(const std::string_view name) {
        if (variables.contains(name.data()))
            return variables[name.data()];
        if (parentScope != nullptr)
            return parentScope->getVariable(name);

        throw std::runtime_error("Variable not found: " + std::string(name));
    }

    std::shared_ptr<Jago::JagoMethod> JagoScope::getFunction(const std::string_view name) {
        if (functions.contains(name.data()))
            return functions[name.data()];
        if (parentScope != nullptr)
            return parentScope->getFunction(name);

        throw std::runtime_error("Function not found: " + std::string(name));
    }

    void JagoScope::setVariable(std::string_view name, Jago::JagoValue value) {
        variables.insert_or_assign(name.data(), std::move(value));
    }

    void JagoScope::setFunction(std::string_view name, std::shared_ptr<Jago::JagoMethod> method) {
        functions.insert_or_assign(name.data(), method);
    }

    void JagoScope::dump(std::ostream &out) const {
        for (const auto &[name, value]: variables) {
            out << "Variable: " << name << " = " << value << std::endl;
        }

        for (const auto &[name, method]: functions) {
            out << "Function: " << name << std::endl;
        }
    }
    bool JagoScope::hasVariable(const std::string &string) const {
        return this->variables.contains(string);
    }
} // Jago