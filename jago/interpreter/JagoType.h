//
// Created by creep on 12/14/2022.
//

#ifndef JAGO_JAGOTYPE_H
#define JAGO_JAGOTYPE_H

#include <string>
#include <unordered_map>
#include "JagoMethod.h"
#include "JagoField.h"

namespace Jago {
    class JagoType {
    protected:
        std::string typeName;
        std::unordered_map<std::string, JagoMethod*> declaredMethods;
        std::unordered_map<std::string, JagoField*> declaredFields;
    public:
        explicit JagoType(std::string typeName);

        JagoMethod* GetMethod(const std::string& name);
        JagoField* GetField(const std::string& name);
    };
}


#endif //JAGO_JAGOTYPE_H
