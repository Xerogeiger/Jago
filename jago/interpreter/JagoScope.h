//
// Created by creep on 1/12/2025.
//

#ifndef JAGOSCOPE_H
#define JAGOSCOPE_H
#include <map>
#include <string>

namespace Jago {
    class JagoMethod;
    class JagoValue;

    class JagoScope {
    protected:
        JagoScope* parentScope = nullptr;

        std::map<std::string_view, JagoMethod> functions;
        std::map<std::string_view, JagoValue> variables;

    public:
        explicit JagoScope(JagoScope* parentScope = nullptr) : parentScope(parentScope) {}

        [[nodiscard]] JagoValue getVariable(std::string_view name);
        [[nodiscard]] JagoMethod getFunction(std::string_view name);

        void setVariable(std::string_view name, Jago::JagoValue value);

        void setFunction(std::string_view name, Jago::JagoMethod method);

        void dump(std::ostream &out);

        bool hasVariable(const std::string & string) const;
    };

} // Jago

#endif //JAGOSCOPE_H
