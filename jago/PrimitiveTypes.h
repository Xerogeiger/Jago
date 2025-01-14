//
// Created by creep on 2/5/2023.
//

#ifndef JAGO_JAGOTYPE_H
#define JAGO_JAGOTYPE_H

namespace Jago {
    enum PrimitiveTypes {
        VOID = 0x00,

        BYTE   = 0x01,
        SHORT  = 0x02,
        INT    = 0x03,
        LONG   = 0x04,

        FLOAT  = 0x05,
        DOUBLE = 0x06,

        CHAR   = 0x07,

        BOOLEAN = 0x08,

        STRING = 0x09,

        OBJECT = 0x0A
    };
}

#endif //JAGO_JAGOTYPE_H
