//
// Created by creep on 12/14/2022.
//

#ifndef JAGO_JAGONATIVEMETHOD_H
#define JAGO_JAGONATIVEMETHOD_H

#include <functional>
#include <vector>
#include <string>
#include "JagoMethod.h"
#include "JagoType.h"

namespace Jago {
    class JagoNativeMethod: public JagoMethod {
    public:
        std::function<JagoVariable*(JagoVariable*, int)> methodFunction;

        JagoNativeMethod(const std::string& name, Jago::JagoType *returnType,
                         const std::vector<Jago::JagoType *>& argumentTypes,
                         std::function<JagoVariable*(JagoVariable*, int)> underlyingFunction);

        JagoVariable* Invoke(JagoVariable *arguments, int argumentLength) override;
    };
}

#endif //JAGO_JAGONATIVEMETHOD_H
