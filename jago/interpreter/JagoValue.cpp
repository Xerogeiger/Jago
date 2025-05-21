#include "JagoValue.h"
#include "JagoType.h"

namespace Jago {
    std::string JagoValue::asString() const {
        if (std::holds_alternative<std::string>(value)) {
            return std::get<std::string>(value);
        } else if (std::holds_alternative<double>(value)) {
            return std::to_string(std::get<double>(value));
        } else if (std::holds_alternative<int>(value)) {
            return std::to_string(std::get<int>(value));
        } else if (std::holds_alternative<bool>(value)) {
            return std::get<bool>(value) ? "true" : "false";
        } else if (std::holds_alternative<char>(value)) {
            return std::string{std::get<char>(value)};
        } else if (std::holds_alternative<int16_t>(value)) {
            return std::to_string(std::get<int16_t>(value));
        } else if (std::holds_alternative<int8_t>(value)) {
            return std::to_string(std::get<int8_t>(value));
        } else if (std::holds_alternative<int64_t>(value)) {
            return std::to_string(std::get<int64_t>(value));
        } else if (std::holds_alternative<float>(value)) {
            return std::to_string(std::get<float>(value));
        } else {
            throw std::runtime_error("Cannot convert to string type: " + type.getTypeName());
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
        } else if (std::holds_alternative<bool>(value)) {
            return std::get<bool>(value) ? 1 : 0;
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

    JagoValue JagoValue::castToType(const JagoType& targetType) const {
        if (targetType == Type::STRING) {
            return JagoValue(this->asString());
        } else if (targetType == Type::DOUBLE) {
            return JagoValue(this->asDouble());
        } else if (targetType == Type::INT) {
            return JagoValue(this->asInt());
        } else if (targetType == Type::BOOLEAN) {
            return JagoValue(std::get<bool>(value));
        } else if (targetType == Type::CHAR) {
            return JagoValue(std::get<char>(value));
        } else if (targetType == Type::LONG) {
            return JagoValue(this->asLong());
        } else if (targetType == Type::BYTE) {
            return JagoValue(std::get<int8_t>(value));
        } else if (targetType == Type::SHORT) {
            return JagoValue(std::get<int16_t>(value));
        } else if (targetType == Type::FLOAT) {
            return JagoValue(std::get<float>(value));
        } else {
            throw std::runtime_error("Cannot cast to type: " + targetType.getTypeName());
        }
    }

    bool JagoValue::operator==(const JagoValue &other) const {
        if (&this->type == &Type::VOID || &other.type == &Type::VOID) {
            return false;
        } else if (this->type == Type::STRING) {
            if (other.type == Type::STRING) {
                return this->asString() == other.asString();
            } else {
                return false;
            }
        } else {
            if (this->type == Type::DOUBLE || other.type == Type::DOUBLE) {
                return this->asDouble() == other.asDouble();
            } else if (this->type == Type::FLOAT || other.type == Type::FLOAT) {
                return this->asDouble() == other.asDouble();
            } else if (this->type == Type::LONG || other.type == Type::LONG) {
                return this->asLong() == other.asLong();
            } else if (this->type == Type::INT || other.type == Type::INT) {
                return this->asInt() == other.asInt();
            } else if (this->type == Type::CHAR || other.type == Type::CHAR) {
                return this->asString() == other.asString();
            } else if (this->type == Type::BOOLEAN || other.type == Type::BOOLEAN) {
                return this->asLong() == other.asLong();
            } else {
                return false;
            }
        }
    }

    bool JagoValue::operator>(const JagoValue &other) const {
        return this->asDouble() > other.asDouble();
    }

    bool JagoValue::operator<(const JagoValue &other) const {
        return this->asDouble() < other.asDouble();
    }

    bool JagoValue::operator>=(const JagoValue &other) const {
        return this->asDouble() >= other.asDouble();
    }

    bool JagoValue::operator<=(const JagoValue &other) const {
        return this->asDouble() <= other.asDouble();
    }

    JagoValue &JagoValue::operator=(int value) {
        this->type = Type::INT;
        this->value = value;
        return *this;
    }

    JagoValue &JagoValue::operator=(double value) {
        this->type = Type::DOUBLE;
        this->value = value;
        return *this;
    }

    JagoValue &JagoValue::operator=(float value) {
        this->type = Type::FLOAT;
        this->value = value;
        return *this;

    }

    JagoValue &JagoValue::operator=(char value) {
        this->type = Type::CHAR;
        this->value = value;
        return *this;
    }

    JagoValue &JagoValue::operator=(const std::string &value) {
        this->type = Type::STRING;
        this->value = value;
        return *this;
    }

    JagoValue &JagoValue::operator=(bool value) {
        this->type = Type::BOOLEAN;
        this->value = value;
        return *this;
    }

    JagoValue &JagoValue::operator=(int64_t value) {
        this->type = Type::LONG;
        this->value = value;
        return *this;
    }

    std::ostream &operator<<(std::ostream &out, const JagoValue &value) {
        if (value.type == Type::STRING) {
            out << "String Value: " << std::get<std::string>(value.value);
        } else if (value.type == Type::DOUBLE) {
            out << "Double Value: " << std::to_string(std::get<double>(value.value));
        } else if (value.type == Type::FLOAT) {
            out << "Float Value: " << std::to_string(std::get<float>(value.value));
        } else if (value.type == Type::INT) {
            out << "Int Value: " << std::to_string(std::get<int>(value.value));
        } else if (value.type == Type::LONG) {
            out << "Long Value: " << std::to_string(std::get<int64_t>(value.value));
        } else if (value.type == Type::SHORT) {
            out << "Short Value: " << std::to_string(std::get<int16_t>(value.value));
        } else if (value.type == Type::BYTE) {
            out << "Byte Value: " << std::to_string(std::get<int8_t>(value.value));
        } else if (value.type == Type::CHAR) {
            out << "Char Value: " << std::to_string(std::get<char>(value.value));
        } else if (value.type == Type::BOOLEAN) {
            out << "Bool Value: " << (std::get<bool>(value.value) ? "true" : "false");
        } else if (value.type == Type::VOID) {
            out << "Void Value: void";
        } else {
            out << "null";
        }

        return out;
    }
} // namespace Jago