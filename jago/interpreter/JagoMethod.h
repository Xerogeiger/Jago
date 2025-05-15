//
// Created by creep on 1/12/2025.
//

#ifndef JAGOMETHOD_H
#define JAGOMETHOD_H
#include <memory>

#include "AST/ASTNode.h"
#include "JagoScope.h"
#include "JagoValue.h"


namespace Jago {
    struct JagoParameter {
        JagoType type;
        std::string name;
    };

    class JagoMethod {
    private:
        std::unique_ptr<ASTNode> body;
        std::vector<JagoParameter> parameters;

    public:
        JagoMethod() = default;

        JagoMethod(std::unique_ptr<ASTNode> body, std::vector<JagoParameter> parameters) : body(std::move(body)), parameters(std::move(parameters)) {}

        [[nodiscard]] std::vector<JagoParameter> getParameters() const {
            return parameters;
        }

        JagoValue invoke(JagoScope& methodScope) {
            return {};
        }
    };
}



#endif //JAGOMETHOD_H
