//
// Created by creep on 12/14/2022.
//

#ifndef JAGO_JAGOSCOPE_H
#define JAGO_JAGOSCOPE_H

#include <unordered_map>
#include <string>
#include "JagoType.h"
#include "JagoVariable.h"
#include "JagoMethod.h"
#include "JagoField.h"

namespace Jago {
    class JagoScope {
    protected:
        std::unordered_map<std::string, JagoVariable*> DeclaredVariables;
        std::unordered_map<std::string, JagoMethod*> DeclaredMethods;
        std::unordered_map<std::string, JagoField*> DeclaredFields;
        std::unordered_map<std::string, JagoType*> DeclaredTypes;
    public:
        void AddVariable(const std::string& name, JagoVariable* variable);
        void AddMethod(const std::string& name, JagoMethod* method);
        void AddField(const std::string& name, JagoField* field);
        void AddType(const std::string& name, JagoType* type);

        JagoVariable* GetVariable(const std::string& variableName);
        JagoMethod* GetMethod(const std::string& methodName);
        JagoField* GetField(const std::string& fieldName);
        JagoType* GetType(const std::string& typeName);

        bool ContainsVariable(const std::string& variableName);
        bool ContainsMethod(const std::string& methodName);
        bool ContainsField(const std::string& fieldName);
        bool ContainsType(const std::string& typeName);

        bool IsNameDeclared(const std::string& name);
    };
}

#endif //JAGO_JAGOSCOPE_H
