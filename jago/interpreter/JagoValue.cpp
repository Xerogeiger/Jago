//
// Created by creep on 1/13/2025.
// Added assignment operator overloads for various types
//

#include "JagoValue.h"

namespace Jago {
    std::string JagoValue::asString() const {
        if (std::holds_alternative<std::shared_ptr<std::string>>(value)) {
            return *std::get<std::shared_ptr<std::string>>(value);
        } else if (std::holds_alternative<double>(value)) {
            return std::to_string(std::get<double>(value));
        } else if (std::holds_alternative<int>(value)) {
            return std::to_string(std::get<int>(value));
        } else if (std::holds_alternative<bool>(value)) {
            return std::get<bool>(value) ? "true" : "false";
        } else if (std::holds_alternative<char>(value)) {
            return std::string{std::get<char>(value)};
        } else {
            throw std::runtime_error("Cannot convert to string type to string " + std::to_string(type));
        }
    }

    double JagoValue::asDouble() const {
        if (std::holds_alternative<float>(value)) {
            return static_cast<double>(std::get<float>(value));
        } else if (std::holds_alternative<double>(value)) {
            return std::get<double>(value);
        } else if (std::holds_alternative<char>(value)) {
            return static_cast<double>(std::get<char>(value));
        } else if (std::holds_alternative<int16_t>(value)) {
            return static_cast<double>(std::get<int16_t>(value));
        } else if (std::holds_alternative<int8_t>(value)) {
            return static_cast<double>(std::get<int8_t>(value));
        } else if (std::holds_alternative<int64_t>(value)) {
            return static_cast<double>(std::get<int64_t>(value));
        } else if (std::holds_alternative<int>(value)) {
            return static_cast<double>(std::get<int>(value));
        } else {
            return 0;
        }
    }

    int64_t JagoValue::asLong() const {
        if (std::holds_alternative<float>(value)) {
            return static_cast<int64_t>(std::get<float>(value));
        } else if (std::holds_alternative<double>(value)) {
            return static_cast<int64_t>(std::get<double>(value));
        } else if (std::holds_alternative<char>(value)) {
            return static_cast<int64_t>(std::get<char>(value));
        } else if (std::holds_alternative<int16_t>(value)) {
            return static_cast<int64_t>(std::get<int16_t>(value));
        } else if (std::holds_alternative<int8_t>(value)) {
            return static_cast<int64_t>(std::get<int8_t>(value));
        } else if (std::holds_alternative<int64_t>(value)) {
            return std::get<int64_t>(value);
        } else if (std::holds_alternative<int>(value)) {
            return static_cast<int64_t>(std::get<int>(value));
        } else {
            return 0;
        }
    }

    int32_t JagoValue::asInt() const {
        if (std::holds_alternative<float>(value)) {
            return static_cast<int32_t>(std::get<float>(value));
        } else if (std::holds_alternative<double>(value)) {
            return static_cast<int32_t>(std::get<double>(value));
        } else if (std::holds_alternative<char>(value)) {
            return static_cast<int32_t>(std::get<char>(value));
        } else if (std::holds_alternative<int16_t>(value)) {
            return static_cast<int32_t>(std::get<int16_t>(value));
        } else if (std::holds_alternative<int8_t>(value)) {
            return static_cast<int32_t>(std::get<int8_t>(value));
        } else if (std::holds_alternative<int64_t>(value)) {
            return static_cast<int32_t>(std::get<int64_t>(value));
        } else if (std::holds_alternative<int>(value)) {
            return static_cast<int32_t>(std::get<int>(value));
        } else {
            return 0;
        }
    }

    JagoValue JagoValue::castToType(const PrimitiveTypes type) const {
        switch (type) {
            case PrimitiveTypes::STRING:
                return JagoValue(this->asString());
            case PrimitiveTypes::DOUBLE:
                return JagoValue(this->asDouble());
            case PrimitiveTypes::INT:
                return JagoValue(this->asInt());
            case PrimitiveTypes::BOOLEAN:
                return JagoValue(std::get<bool>(value));
            case PrimitiveTypes::CHAR:
                return JagoValue(std::get<char>(value));
            case PrimitiveTypes::LONG:
                return JagoValue(this->asLong());
            case PrimitiveTypes::BYTE:
                return JagoValue(std::get<int8_t>(value));
            case PrimitiveTypes::SHORT:
                return JagoValue(std::get<int16_t>(value));
            case PrimitiveTypes::FLOAT:
                return JagoValue(std::get<float>(value));
            default:
                throw std::runtime_error("Cannot cast to type " + std::to_string(type));
        }
    }

    bool JagoValue::operator==(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (this->type == PrimitiveTypes::STRING) {
                return this->toString() == other.toString();
            } else if (this->type == PrimitiveTypes::DOUBLE) {
                return this->toDouble() == other.toDouble();
            } else if (this->type == PrimitiveTypes::FLOAT) {
                return this->toFloat() == other.toFloat();
            } else if (this->type == PrimitiveTypes::INT) {
                return this->toInt() == other.toInt();
            } else if (this->type == PrimitiveTypes::BOOLEAN) {
                return this->toBool() == other.toBool();
            } else if (this->type == PrimitiveTypes::CHAR) {
                return this->toChar() == other.toChar();
            } else if (this->toByte() == other.toByte()) {
                return this->toByte() == other.toByte();
            } else if (this->toShort() == other.toShort()) {
                return this->toShort() == other.toShort();
            } else if (this->toLong() == other.toLong()) {
                return this->toLong() == other.toLong();
            }

            return false;
        }
    }
    bool JagoValue::operator>(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (std::holds_alternative<std::shared_ptr<std::string>>(value)) {
                return this->toString() > other.toString();
            } else if (std::holds_alternative<double>(value)) {
                return this->toDouble() > other.toDouble();
            } else if (std::holds_alternative<float>(value)) {
                return this->toFloat() > other.toFloat();
            } else if (std::holds_alternative<int>(value)) {
                return this->toInt() > other.toInt();
            } else if (std::holds_alternative<bool>(value)) {
                return this->toBool() > other.toBool();
            } else if (std::holds_alternative<char>(value)) {
                return this->toChar() > other.toChar();
            } else if (std::holds_alternative<int8_t>(value)) {
                return this->toByte() > other.toByte();
            } else if (std::holds_alternative<int16_t>(value)) {
                return this->toShort() > other.toShort();
            }
        }

        return false;
    }
    bool JagoValue::operator<(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            if (std::holds_alternative<std::shared_ptr<std::string>>(value)) {
                return this->toString() < other.toString();
            } else if (std::holds_alternative<double>(value)) {
                return this->toDouble() < other.toDouble();
            } else if (std::holds_alternative<float>(value)) {
                return this->toFloat() < other.toFloat();
            } else if (std::holds_alternative<int>(value)) {
                return this->toInt() < other.toInt();
            } else if (std::holds_alternative<bool>(value)) {
                return this->toBool() < other.toBool();
            } else if (std::holds_alternative<char>(value)) {
                return this->toChar() < other.toChar();
            } else if (std::holds_alternative<int8_t>(value)) {
                return this->toByte() < other.toByte();
            } else if (std::holds_alternative<int16_t>(value)) {
                return this->toShort() < other.toShort();
            }
        }

        return false;
    }
    bool JagoValue::operator>=(const JagoValue &other) const {
        if (this->type == PrimitiveTypes::VOID || other.type == PrimitiveTypes::VOID) {
            return false;
        } else if (this->type != other.type) {
            return false;
        } else {
            return this->operator>(other) || this->operator==(other);
        }
    }

    bool JagoValue::operator<=(const JagoValue &other) const {
        return this->operator<(other) || this->operator==(other);
    }
    JagoValue &JagoValue::operator=(const int value) {
        this->type = PrimitiveTypes::INT;
        this->value = value;
        return *this;
    }
    JagoValue &JagoValue::operator=(const double value) {
        this->type = PrimitiveTypes::DOUBLE;
        this->value = value;
        return *this;
    }
    JagoValue &JagoValue::operator=(const float value) {
        this->type = PrimitiveTypes::FLOAT;
        this->value = value;
        return *this;
    }
    JagoValue &JagoValue::operator=(const char value) {
        this->type = PrimitiveTypes::CHAR;
        this->value = value;
        return *this;
    }
    JagoValue &JagoValue::operator=(const std::string &value) {
        this->type = PrimitiveTypes::STRING;
        this->value = std::make_shared<std::string>(value);
        return *this;
    }
    JagoValue &JagoValue::operator=(const bool value) {
        this->type = PrimitiveTypes::BOOLEAN;
        this->value = value;
        return *this;
    }
    JagoValue &JagoValue::operator=(const int64_t value) {
        this->type = PrimitiveTypes::LONG;
        this->value = value;
        return *this;
    }

    std::ostream &operator<<(std::ostream &out, const JagoValue &value) {
        switch (value.type) {
            case PrimitiveTypes::STRING:
                out << std::string("String Value: ") << *std::get<std::shared_ptr<std::string>>(value.value);
                break;
            case PrimitiveTypes::DOUBLE:
                out << std::string("Double Value: ") << std::to_string(std::get<double>(value.value));
                break;
            case PrimitiveTypes::FLOAT:
                out << std::string("Float Value: ") << std::to_string(std::get<float>(value.value));
                break;
            case PrimitiveTypes::INT:
                out << std::string("Int Value: ") << std::to_string(std::get<int>(value.value));
                break;
            case PrimitiveTypes::LONG:
                out << std::string("Long Value: ") << std::to_string(std::get<int64_t>(value.value));
                break;
            case PrimitiveTypes::SHORT:
                out << std::string("Short Value: ") << std::to_string(std::get<int16_t>(value.value));
                break;
            case PrimitiveTypes::BYTE:
                out << std::string("Byte Value: ") << std::to_string(std::get<int8_t>(value.value));
                break;
            case PrimitiveTypes::CHAR:
                out << std::string("Char Value: ") << std::to_string(std::get<char>(value.value));
                break;
            case PrimitiveTypes::BOOLEAN:
                out << std::string("Bool Value: ") << std::string(std::get<bool>(value.value) ? "true" : "false");
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