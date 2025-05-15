//
// Created by creep on 2/5/2023.
//

#ifndef JAGO_JAGOTYPE_H
#define JAGO_JAGOTYPE_H

#include <ostream>

namespace Jago {
    enum class PrimitiveTypes {
        VOID = 0x00,

        BYTE = 0x01,
        SHORT = 0x02,
        INT = 0x03,
        LONG = 0x04,

        FLOAT = 0x05,
        DOUBLE = 0x06,

        CHAR = 0x07,

        BOOLEAN = 0x08,

        STRING = 0x09,

        OBJECT = 0x0A
    };

    inline std::ostream& operator<<(std::ostream& os, PrimitiveTypes type) {
        switch (type) {
            case PrimitiveTypes::VOID:
                os << "void";
                break;
            case PrimitiveTypes::BYTE:
                os << "byte";
                break;
            case PrimitiveTypes::SHORT:
                os << "short";
                break;
            case PrimitiveTypes::INT:
                os << "int";
                break;
            case PrimitiveTypes::LONG:
                os << "long";
                break;
            case PrimitiveTypes::FLOAT:
                os << "float";
                break;
            case PrimitiveTypes::DOUBLE:
                os << "double";
                break;
            case PrimitiveTypes::CHAR:
                os << "char";
                break;
            case PrimitiveTypes::BOOLEAN:
                os << "boolean";
                break;
            case PrimitiveTypes::STRING:
                os << "string";
                break;
            case PrimitiveTypes::OBJECT:
                os << "object";
                break;
        }

        return os;
    }
}

#endif //JAGO_JAGOTYPE_H
