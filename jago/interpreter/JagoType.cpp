//
// Created by creep on 12/14/2022.
//

#include "JagoType.h"

Jago::JagoType::JagoType(std::string typeName) {
    this->typeName = std::move(typeName);
}

Jago::JagoMethod *Jago::JagoType::GetMethod(const std::string &name) {
    return this->declaredMethods[name];
}

Jago::JagoField *Jago::JagoType::GetField(const std::string &name) {
    return this->declaredFields[name];
}
