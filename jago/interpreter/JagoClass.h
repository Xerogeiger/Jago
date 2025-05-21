//
// Created by creep on 5/20/2025.
//

#ifndef JAGOCLASS_H
#define JAGOCLASS_H

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "JagoScope.h"
#include "JagoMethod.h"

namespace Jago {

class JagoClass {
    protected:
        std::string name;
        std::vector<std::shared_ptr<JagoMethod>> methods;

    public:
        explicit JagoClass(std::string name) : name(std::move(name)) {}

        void addMethod(std::shared_ptr<JagoMethod> method) {
            methods.push_back(std::move(method));
        }

        [[nodiscard]] std::vector<std::shared_ptr<JagoMethod>> getMethods() const {
            return methods;
        }

        [[nodiscard]] std::string getTypeName() const { return name; }

        [[nodiscard]] std::string getName() const { return name; }
        [[nodiscard]] std::shared_ptr<JagoMethod> getMethod(const std::string &name);
};

} // Jago

#endif //JAGOCLASS_H
