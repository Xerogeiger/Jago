//
// Created by creep on 12/14/2022.
//

#include "JagoScope.h"

Jago::JagoVariable *Jago::JagoScope::GetVariable(const std::string& variableName) {
    return this->DeclaredVariables[variableName];
}

Jago::JagoMethod *Jago::JagoScope::GetMethod(const std::string& methodName) {
    return this->DeclaredMethods[methodName];
}

Jago::JagoField *Jago::JagoScope::GetField(const std::string &fieldName) {
    return this->DeclaredFields[fieldName];
}

Jago::JagoType *Jago::JagoScope::GetType(const std::string &typeName) {
    return this->DeclaredTypes[typeName];
}

bool Jago::JagoScope::IsNameDeclared(const std::string& name) {
    return this->DeclaredMethods.find(name) != this->DeclaredMethods.end() ||
           this->DeclaredVariables.find(name) != this->DeclaredVariables.end() ||
            this->DeclaredFields.find(name) != this->DeclaredFields.end() ||
            this->DeclaredTypes.find(name) != this->DeclaredTypes.end();
}

void Jago::JagoScope::AddVariable(const std::string& name, Jago::JagoVariable *variable) {
    this->DeclaredVariables[name] = variable;
}

void Jago::JagoScope::AddMethod(const std::string &name, Jago::JagoMethod *method) {
    this->DeclaredMethods[name] = method;
}

void Jago::JagoScope::AddField(const std::string &name, Jago::JagoField *field) {
    this->DeclaredFields[name] = field;
}

void Jago::JagoScope::AddType(const std::string &name, Jago::JagoType *type) {
    this->DeclaredTypes[name] = type;
}

bool Jago::JagoScope::ContainsVariable(const std::string &variableName) {
    return this->DeclaredVariables.find(variableName) != this->DeclaredVariables.end();
}

bool Jago::JagoScope::ContainsMethod(const std::string &methodName) {
    return this->DeclaredMethods.find(methodName) != this->DeclaredMethods.end();
}

bool Jago::JagoScope::ContainsField(const std::string &fieldName) {
    return this->DeclaredFields.find(fieldName) != this->DeclaredFields.end();
}

bool Jago::JagoScope::ContainsType(const std::string &typeName) {
    return this->DeclaredTypes.find(typeName) != this->DeclaredTypes.end();
}

