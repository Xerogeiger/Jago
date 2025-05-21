//
// Created by creep on 1/12/2025.
//

#include "JagoMethod.h"
#include "AST/Visitor.h"

Jago::JagoValue Jago::JagoMethod::invoke(Visitor &visitor, std::shared_ptr<JagoScope> methodScope) {
    body->accept(visitor);
    return visitor.getResult();
}
