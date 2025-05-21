//
// Created by creep on 1/12/2025.
//

#ifndef JAGOMETHOD_H
#define JAGOMETHOD_H
#include <functional>
#include <memory>
#include <utility>

#include "AST/ASTNode.h"
#include "JagoScope.h"
#include "JagoValue.h"


namespace Jago {

    class Visitor;

    struct JagoParameter {
        JagoType type;
        std::string name;
    };

    class JagoMethod {
    protected:
        std::unique_ptr<ASTNode> body;
        std::vector<JagoParameter> parameters;
        std::string name;

    public:
        virtual ~JagoMethod() = default;
        JagoMethod() = default;

        JagoMethod(std::string name, std::unique_ptr<ASTNode> body, std::vector<JagoParameter> parameters) : name(std::move(name)), body(std::move(body)), parameters(std::move(parameters)) {}

        [[nodiscard]] std::vector<JagoParameter> getParameters() const {
            return parameters;
        }

        std::string getName() {
            return name;
        }

        virtual JagoValue invoke(Visitor &visitor, std::shared_ptr<JagoScope> methodScope);
    };

    class NativeMethod : public JagoMethod {
        std::function<JagoValue(std::shared_ptr<JagoScope> scope)> function;
    public:
        NativeMethod(std::string name, std::vector<JagoParameter> parameters, std::function<JagoValue(std::shared_ptr<JagoScope> scope)> function) : JagoMethod(std::move(name), nullptr, std::move(parameters)), function(std::move(function)) {}
        JagoValue invoke(Visitor &visitor, std::shared_ptr<JagoScope> methodScope) override {
            return function(methodScope);
        }
    };
}



#endif //JAGOMETHOD_H
