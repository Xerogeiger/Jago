//
// Created by creep on 12/14/2022.
//

#include "JagoVariable.h"

Jago::JagoVariable::JagoVariable(const std::string &name, Jago::JagoType *variableType) {
    this->variableName = name;
    this->variableType = variableType;
}

Jago::JagoVariable::JagoVariable(const std::string &name, Jago::JagoType *variableType, uint64_t value) {
    this->variableName = name;
    this->variableType = variableType;
    this->variableValue = value;
}

template<typename T>
T Jago::JagoVariable::GetValue() {
    return reinterpret_cast<T>(this->variableValue);
}

template<typename T>
void Jago::JagoVariable::SetValue(T value) {
    this->template SetValue<uint64_t>(value);
}
