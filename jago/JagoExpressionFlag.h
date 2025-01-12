//
// Created by creep on 2/2/2023.
//

#ifndef JAGO_JAGOEXPRESSIONFLAG_H
#define JAGO_JAGOEXPRESSIONFLAG_H

#include <cstdint>

namespace Jago {
    enum ExpressionFlag: uint_16 {
        Private   = 0b00000000,
        Default   = 0b00000001,
        Protected = 0b00000011,
        Public    = 0b00000111,

        Static    = 0b00001000,
        Constant  = 0b00010000,
        Abstract  = 0b00100000,
    };
}

#endif //JAGO_JAGOEXPRESSIONFLAG_H
