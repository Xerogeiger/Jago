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
            default:
                return 0;
        }
    }
    bool JagoValue::operator==(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (this->type == PrimitiveTypes::STRING) {
                return *this->value.stringValue == *other.value.stringValue;
            } else if (this->type == PrimitiveTypes::DOUBLE) {
                return this->value.doubleValue == other.value.doubleValue;
            } else if (this->type == PrimitiveTypes::INT) {
                return this->value.intValue == other.value.intValue;
            } else if (this->type == PrimitiveTypes::BOOLEAN) {
                return this->value.boolValue == other.value.boolValue;
            } else if (this->type == PrimitiveTypes::CHAR) {
                return this->value.charValue == other.value.charValue;
            } else {
                return this->value.pointerValue == other.value.pointerValue;
            }
        }
    }
    bool JagoValue::operator>(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (this->type == PrimitiveTypes::STRING) {
                return *this->value.stringValue > *other.value.stringValue;
            } else if (this->type == PrimitiveTypes::DOUBLE) {
                return this->value.doubleValue > other.value.doubleValue;
            } else if (this->type == PrimitiveTypes::INT) {
                return this->value.intValue > other.value.intValue;
            } else if (this->type == PrimitiveTypes::BOOLEAN) {
                return this->value.boolValue > other.value.boolValue;
            } else if (this->type == PrimitiveTypes::CHAR) {
                return this->value.charValue > other.value.charValue;
            } else {
                return this->value.pointerValue > other.value.pointerValue;
            }
        }
    }
    bool JagoValue::operator<(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (this->type == PrimitiveTypes::STRING) {
                return *this->value.stringValue < *other.value.stringValue;
            } else if (this->type == PrimitiveTypes::DOUBLE) {
                return this->value.doubleValue < other.value.doubleValue;
            } else if (this->type == PrimitiveTypes::INT) {
                return this->value.intValue < other.value.intValue;
            } else if (this->type == PrimitiveTypes::BOOLEAN) {
                return this->value.boolValue < other.value.boolValue;
            } else if (this->type == PrimitiveTypes::CHAR) {
                return this->value.charValue < other.value.charValue;
            } else {
                return this->value.pointerValue < other.value.pointerValue;
            }
        }
    }
    bool JagoValue::operator>=(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (this->type == PrimitiveTypes::STRING) {
                return *this->value.stringValue >= *other.value.stringValue;
            } else if (this->type == PrimitiveTypes::DOUBLE) {
                return this->value.doubleValue >= other.value.doubleValue;
            } else if (this->type == PrimitiveTypes::INT) {
                return this->value.intValue >= other.value.intValue;
            } else if (this->type == PrimitiveTypes::BOOLEAN) {
                return this->value.boolValue >= other.value.boolValue;
            } else if (this->type == PrimitiveTypes::CHAR) {
                return this->value.charValue >= other.value.charValue;
            } else {
                return this->value.pointerValue >= other.value.pointerValue;
            }
        }
    }

    bool JagoValue::operator<=(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (this->type == PrimitiveTypes::STRING) {
                return *this->value.stringValue <= *other.value.stringValue;
            } else if (this->type == PrimitiveTypes::DOUBLE) {
                return this->value.doubleValue <= other.value.doubleValue;
            } else if (this->type == PrimitiveTypes::INT) {
                return this->value.intValue <= other.value.intValue;
            } else if (this->type == PrimitiveTypes::BOOLEAN) {
                return this->value.boolValue <= other.value.boolValue;
            } else if (this->type == PrimitiveTypes::CHAR) {
                return this->value.charValue <= other.value.charValue;
            } else {
                return this->value.pointerValue <= other.value.pointerValue;
            }
        }
    }

    std::ostream &operator<<(std::ostream &out, const JagoValue &value) {
        switch (value.type) {
            case PrimitiveTypes::STRING:
                out << std::string("String Value: ") << *value.value.stringValue;
                break;
            case PrimitiveTypes::DOUBLE:
                out << std::string("Double Value: ") << std::to_string(value.value.doubleValue);
                break;
            case PrimitiveTypes::FLOAT:
                out << std::string("Float Value: ") << std::to_string(value.value.floatValue);
                break;
            case PrimitiveTypes::INT:
                out << std::string("Int Value: ") << std::to_string(value.value.intValue);
                break;
            case PrimitiveTypes::LONG:
                out << std::string("Long Value: ") << std::to_string(value.value.longValue);
                break;
            case PrimitiveTypes::SHORT:
                out << std::string("Short Value: ") << std::to_string(value.value.shortValue);
                break;
            case PrimitiveTypes::BYTE:
                out << std::string("Byte Value: ") << std::to_string(value.value.byteValue);
                break;
            case PrimitiveTypes::CHAR:
                out << std::string("Char Value: ") << std::to_string(value.value.charValue);
                break;
            case PrimitiveTypes::BOOLEAN:
                out << std::string("Bool Value: ") << std::string(value.value.boolValue ? "true" : "false");
                break;
            case PrimitiveTypes::VOID:
                out << std::string("Void Value: ") << std::string("void");
                break;
            default:
                out << std::string("null");
        }

        return out;
    }
} // Jago