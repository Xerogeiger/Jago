//
// Created by creep on 12/14/2022.
//

#ifndef JAGO_JAGOBYTECODES_H
#define JAGO_JAGOBYTECODES_H

#include <cstdint>

namespace Jago {
    enum ByteCode: uint8_t {
        NO_OPERATION,
        CLEAR_STACK,

        METHOD_CALL,

        DEFINE_VARIABLE_8,
        DEFINE_VARIABLE_16,
        DEFINE_VARIABLE_32,
        DEFINE_VARIABLE_64,

        SET_VARIABLE_8,
        SET_VARIABLE_16,
        SET_VARIABLE_32,
        SET_VARIABLE_64,

        PUSH_8,
        PUSH_16,
        PUSH_32,
        PUSH_64,

        RETURN,

        IF,
        ELSE,
        END_IF,

        IS_EQUAL,
        IS_LESS,
        IS_GREATER,
        IS_GREATER_OR_EQUAL,
        IS_LESS_OR_EQUAL,

        MULTIPLY_INT_8,
        ADD_INT_8,
        SUBTRACT_INT_8,
        DIVIDE_INT_8,

        MULTIPLY_INT_16,
        ADD_INT_16,
        SUBTRACT_INT_16,
        DIVIDE_INT_16,

        MULTIPLY_INT_32,
        ADD_INT_32,
        SUBTRACT_INT_32,
        DIVIDE_INT_32,

        MULTIPLY_INT_64,
        ADD_INT_64,
        SUBTRACT_INT_64,
        DIVIDE_INT_64,

        MULTIPLY_FLOAT_32,
        ADD_FLOAT_32,
        SUBTRACT_FLOAT_32,
        DIVIDE_FLOAT_32,

        MULTIPLY_FLOAT_64,
        ADD_FLOAT_64,
        SUBTRACT_FLOAT_64,
        DIVIDE_FLOAT_64,
    };

    inline std::string ByteCodeToString(ByteCode byteCode) {
        switch (byteCode) {
            case NO_OPERATION: return "NO_OPERATION";
            case CLEAR_STACK: return "CLEAR_STACK";

            case METHOD_CALL: return "METHOD_CALL";

            case DEFINE_VARIABLE_8: return "DEFINE_VARIABLE_8";
            case DEFINE_VARIABLE_16: return "DEFINE_VARIABLE_16";
            case DEFINE_VARIABLE_32: return "DEFINE_VARIABLE_32";
            case DEFINE_VARIABLE_64: return "DEFINE_VARIABLE_64";

            case SET_VARIABLE_8: return "SET_VARIABLE_8";
            case SET_VARIABLE_16: return "SET_VARIABLE_16";
            case SET_VARIABLE_32: return "SET_VARIABLE_32";
            case SET_VARIABLE_64: return "SET_VARIABLE_64";

            case PUSH_8: return "PUSH_8";
            case PUSH_16: return "PUSH_16";
            case PUSH_32: return "PUSH_32";
            case PUSH_64: return "PUSH_64";

            case RETURN: return "RETURN";

            case IF: return "IF";
            case ELSE: return "ELSE";
            case END_IF: return "END_IF";

            case IS_EQUAL: return "IS_EQUAL";
            case IS_LESS: return "IS_LESS";
            case IS_GREATER: return "IS_GREATER";
            case IS_GREATER_OR_EQUAL: return "IS_GREATER_OR_EQUAL";
            case IS_LESS_OR_EQUAL: return "IS_LESS_OR_EQUAL";

            case MULTIPLY_INT_8: return "MULTIPLY_INT_8";
            case ADD_INT_8: return "ADD_INT_8";
            case SUBTRACT_INT_8: return "SUBTRACT_INT_8";
            case DIVIDE_INT_8: return "DIVIDE_INT_8";

            case MULTIPLY_INT_16: return "MULTIPLY_INT_16";
            case ADD_INT_16: return "ADD_INT_16";
            case SUBTRACT_INT_16: return "SUBTRACT_INT_16";
            case DIVIDE_INT_16: return "DIVIDE_INT_16";

            case MULTIPLY_INT_32: return "MULTIPLY_INT_32";
            case ADD_INT_32: return "ADD_INT_32";
            case SUBTRACT_INT_32: return "SUBTRACT_INT_32";
            case DIVIDE_INT_32: return "DIVIDE_INT_32";

            case MULTIPLY_INT_64: return "MULTIPLY_INT_64";
            case ADD_INT_64: return "ADD_INT_64";
            case SUBTRACT_INT_64: return "SUBTRACT_INT_64";
            case DIVIDE_INT_64: return "DIVIDE_INT_64";

            case MULTIPLY_FLOAT_32: return "MULTIPLY_FLOAT_32";
            case ADD_FLOAT_32: return "ADD_FLOAT_32";
            case SUBTRACT_FLOAT_32: return "SUBTRACT_FLOAT_32";
            case DIVIDE_FLOAT_32: return "DIVIDE_FLOAT_32";

            case MULTIPLY_FLOAT_64: return "MULTIPLY_FLOAT_64";
            case ADD_FLOAT_64: return "ADD_FLOAT_64";
            case SUBTRACT_FLOAT_64: return "SUBTRACT_FLOAT_64";
            case DIVIDE_FLOAT_64: return "DIVIDE_FLOAT_64";

            default: return "UNKNOWN_BYTECODE";
        }
    }
}

#endif //JAGO_JAGOBYTECODES_H
