//
// Created by creep on 1/13/2025.
//

#include "JagoValue.h"

namespace Jago {
    std::string JagoValue::asString() const {
        if (type == STRING) {
            return *value.stringValue;
        } else if (type == DOUBLE) {
            return std::to_string(value.doubleValue);
        } else if (type == INT) {
            return std::to_string(value.intValue);
        } else if (type == BOOLEAN) {
            return value.boolValue ? "true" : "false";
        } else if (type == CHAR) {
            return std::string{static_cast<char>(value.charValue)};
        } else {
            return "null";
        }
    }

    double JagoValue::asDouble() const {
        switch (type) {
            case FLOAT:
                return value.floatValue;
            case DOUBLE:
                return value.doubleValue;
            case CHAR:
                return value.charValue;
            case SHORT:
                return value.shortValue;
            case BYTE:
                return value.byteValue;
            case LONG:
                return static_cast<double>(value.longValue);
            case INT:
                return value.intValue;
            default: return 0;
        }
    }

    int64_t JagoValue::asInt() const {
        switch (type) {
            case FLOAT:
                return static_cast<int64_t>(value.floatValue);
            case DOUBLE:
                return static_cast<int64_t>(value.doubleValue);
            case CHAR:
                return value.charValue;
            case SHORT:
                return value.shortValue;
            case BYTE:
                return value.byteValue;
            case LONG:
                return value.longValue;
            case INT:
                return value.intValue;
            default: return 0;
        }
    }
} // Jago