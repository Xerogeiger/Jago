//
// Created by creep on 2/5/2023.
//

#ifndef JAGO_JAGOTYPE_H
#define JAGO_JAGOTYPE_H

#include <string>
#include <string_view>

namespace Jago {
    enum JagoType {
        BYTE   = 0x00,
        SHORT  = 0x01,
        INT    = 0x02,
        LONG   = 0x03,

        FLOAT  = 0x04,
        DOUBLE = 0x05,

        CHAR   = 0x06,

        OBJECT = 0x07
    };
}

#endif //JAGO_JAGOTYPE_H
