//
// Created by creep on 1/12/2025.
//

#ifndef JAGOSCOPE_H
#define JAGOSCOPE_H
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

namespace Jago {
    class JagoMethod;
    class JagoValue;
    class JagoClass;

    class JagoScope {
    protected:
        std::shared_ptr<JagoScope> parentScope;

        std::map<std::string, std::shared_ptr<JagoClass>> classes;
        std::map<std::string, std::shared_ptr<JagoMethod>> functions;
        std::map<std::string, JagoValue> variables;

    public:
        explicit JagoScope(std::shared_ptr<JagoScope> parentScope) : parentScope(std::move(parentScope)) {
            functions = {};
            variables = {};
        }

        [[nodiscard]] JagoValue getVariable(std::string_view name);
        [[nodiscard]] std::shared_ptr<JagoMethod> getFunction(const std::string &name);
        [[nodiscard]] std::shared_ptr<JagoClass> getClass(const std::string &name) {
            if (classes.contains(name)) {
                return classes[name];
            }
            if (parentScope != nullptr) {
                return parentScope->getClass(name);
            }
            return nullptr;
        }

        void setVariable(std::string_view name, Jago::JagoValue value);
        void setClass(const std::string &name, std::shared_ptr<JagoClass> jagoClass) {
            classes[name] = std::move(jagoClass);
        }
        void setFunction(std::string_view name, std::shared_ptr<Jago::JagoMethod> method);

        void dump(std::ostream &out) const;

        bool hasVariable(const std::string &string) const;
        std::shared_ptr<JagoScope> getParentScope() {return parentScope; }

        [[nodiscard]] std::map<std::string, JagoValue> getVariables() const { return variables; }
        [[nodiscard]] std::map<std::string, std::shared_ptr<JagoMethod>> getFunctions() const { return functions; }
    };

} // Jago

#endif //JAGOSCOPE_H
