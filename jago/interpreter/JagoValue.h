//
// Created by creep on 1/13/2025.
//

#ifndef JAGOVALUE_H
#define JAGOVALUE_H
#include <cstdint>
#include <string>
#include <bits/stringfwd.h>

#include "../PrimitiveTypes.h"

namespace Jago {

    class JagoValue {
    public:
        Jago::PrimitiveTypes type;

        union {
            void* pointerValue;
            std::string* stringValue;
            int32_t intValue;
            int64_t longValue;
            int8_t byteValue;
            int8_t charValue;
            int16_t shortValue;
            float floatValue;
            double doubleValue;
            bool boolValue;
        } value{};

        JagoValue() : type(Jago::PrimitiveTypes::VOID), value(nullptr) {}

        JagoValue(const Jago::PrimitiveTypes type, void* value) : type(type) {
            this->value.pointerValue = value;
        }

        // Constructor for std::string*
        JagoValue(const Jago::PrimitiveTypes type, std::string* value) : type(type) {
            this->value.stringValue = value;
        }

        // Constructor for int32_t
        JagoValue(const Jago::PrimitiveTypes type, const int32_t value) : type(type) {
            this->value.intValue = value;
        }

        // Constructor for int64_t
        JagoValue(const Jago::PrimitiveTypes type, const int64_t value) : type(type) {
            this->value.longValue = value;
        }

        // Constructor for int8_t
        JagoValue(const Jago::PrimitiveTypes type, const int8_t value) : type(type) {
            this->value.byteValue = value;
        }

        // Constructor for int16_t
        JagoValue(const Jago::PrimitiveTypes type, const int16_t value) : type(type) {
            this->value.shortValue = value;
        }

        // Constructor for float
        JagoValue(const Jago::PrimitiveTypes type, const float value) : type(type) {
            this->value.floatValue = value;
        }

        // Constructor for double
        JagoValue(const Jago::PrimitiveTypes type, const double value) : type(type) {
            this->value.doubleValue = value;
        }

        // Constructor for bool
        JagoValue(const Jago::PrimitiveTypes type, const bool value) : type(type) {
            this->value.boolValue = value;
        }

        [[nodiscard]] void* toPtr() const noexcept { return value.pointerValue; }
        [[nodiscard]] std::string& toString() const noexcept { return *value.stringValue; }
        [[nodiscard]] int32_t toInt() const noexcept { return value.intValue; }
        [[nodiscard]] int64_t toLong() const noexcept { return value.longValue; }
        [[nodiscard]] int8_t toByte() const noexcept { return value.byteValue; }
        [[nodiscard]] uint8_t toChar() const noexcept { return value.charValue; }
        [[nodiscard]] int16_t toShort() const noexcept { return value.shortValue; }
        [[nodiscard]] float toFloat() const noexcept { return value.floatValue; }
        [[nodiscard]] double toDouble() const noexcept { return value.doubleValue; }
        [[nodiscard]] bool toBool() const noexcept { return value.boolValue; }

        [[nodiscard]] std::string asString() const;
        [[nodiscard]] double asDouble() const;
        [[nodiscard]] int64_t asInt() const;

        bool operator==(const PrimitiveTypes type) const {
            return this->type == type;
        }

        bool operator==(const JagoValue &other) const;
        bool operator>(const JagoValue &other) const;
        bool operator<(const JagoValue &other) const;
        bool operator>=(const JagoValue &other) const;
        bool operator<=(const JagoValue &other) const;

        friend std::ostream& operator<<(std::ostream& out, const JagoValue& value);
    };

} // Jago

#endif //JAGOVALUE_H
