//
// Created by creep on 5/20/2025.
//

#ifndef CLASSDECLARATIONHANDLER_H
#define CLASSDECLARATIONHANDLER_H

#include <string>
#include <vector>

#include "../../JagoToken.h"
#include "../JagoInterpreter.h"

namespace Jago {
    inline struct ClassDeclarationHandler {
        public:
            std::unique_ptr<ClassDeclarationStatement> handle(const JagoInterpreter& interpreter, std::vector<Jago::JagoToken> tokens, int &index);
    } ClassHandler;
}



#endif //CLASSDECLARATIONHANDLER_H
