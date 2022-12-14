//
// Created by creep on 12/14/2022.
//

#include "JagoMethod.h"

Jago::JagoMethod::JagoMethod(const std::string& name, Jago::JagoType *returnType,
                             const std::vector<Jago::JagoType *>& argumentTypes) {
    this->methodName = name;
    this->returnType = returnType;
    this->methodArguments = argumentTypes;
}

Jago::JagoType *Jago::JagoMethod::GetReturnType() const {
    return this->returnType;
}

std::string Jago::JagoMethod::GetMethodName() const {
    return this->methodName;
}

std::vector<Jago::JagoType*> Jago::JagoMethod::GetMethodArguments() const {
    return this->methodArguments;
}
