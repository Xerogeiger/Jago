//
// Created by creep on 5/20/2025.
//

#include "JagoClass.h"

namespace Jago {
    std::shared_ptr<JagoMethod> JagoClass::getMethod(const std::string &name) {
        for (const auto &method: methods) {
            if (method->getName() == name) {
                return method;
            }
        }
        return nullptr;
    }
} // Jago