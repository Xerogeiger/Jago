//
// Created by creep on 5/20/2025.
//

#ifndef JAGOOBJECT_H
#define JAGOOBJECT_H

#include <memory>
#include <string>
#include "JagoClass.h"
#include "JagoScope.h"

namespace Jago {
    class JagoObject {
        protected:
            JagoClass* type;
            std::shared_ptr<JagoScope> scope;
        public:
            JagoObject(JagoClass* type, std::shared_ptr<JagoScope> scope) : type(type), scope(std::move(scope)) {
                if (this->type == nullptr) {
                    throw std::runtime_error("JagoObject type cannot be null");
                }

            }
            virtual ~JagoObject() = default;

            virtual std::string toString() const {
                return "JagoObject{" + type->getName() + "}";
            }

            virtual bool equals(const JagoObject &other) const {
                return this == &other;
            }
    };
}



#endif //JAGOOBJECT_H
