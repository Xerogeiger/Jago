//
// Created by creep on 12/14/2022.
//

#include "JagoNativeMethod.h"

Jago::JagoNativeMethod::JagoNativeMethod(const std::string &name, Jago::JagoType *returnType,
                                         const std::vector<Jago::JagoType *> &argumentTypes,
                                         std::function<JagoVariable *(JagoVariable *, int)> underlyingFunction):
                                         JagoMethod(name, returnType, argumentTypes) {
    this->methodFunction = std::move(underlyingFunction);
}

Jago::JagoVariable *Jago::JagoNativeMethod::Invoke(Jago::JagoVariable *arguments, int argumentLength) {
    return this->methodFunction(arguments, argumentLength);
}


