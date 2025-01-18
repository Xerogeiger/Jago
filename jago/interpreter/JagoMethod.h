//
// Created by creep on 1/12/2025.
//

#ifndef JAGOMETHOD_H
#define JAGOMETHOD_H
#include <memory>

#include "JagoValue.h"
#include "AST/ASTNode.h"


namespace Jago {
    class JagoMethod {
    private:
        std::shared_ptr<ASTNode> body;

    public:
        JagoMethod() = default;

        JagoValue invoke() {
            return {};
        }
    };
}



#endif //JAGOMETHOD_H
