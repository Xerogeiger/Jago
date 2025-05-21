//
// Created by creep on 1/13/2025.
//

#ifndef JAGOVALUE_H
#define JAGOVALUE_H
#include <bits/stringfwd.h>
#include <cstdint>
#include <memory>
#include <string>
#include <variant>

#include "../PrimitiveTypes.h"
#include "JagoType.h"

namespace Jago {

    class JagoValue {
    public:
        JagoType type;

        std::variant<std::monostate,    // for VOID
        int32_t, int64_t, int8_t, int16_t, char, float, double, bool, std::string> value;

        JagoValue() : type(Jago::Type::VOID), value(std::monostate{}) {
        }

        // Constructor for std::string*
        explicit JagoValue(const std::string& value) : type(Jago::Type::STRING), value(value) {
        }

        explicit JagoValue(const int32_t value) : type(Jago::Type::INT), value(value) {
        }

        explicit JagoValue(const int64_t value) : type(Jago::Type::LONG), value(value) {
        }

        explicit JagoValue(const int8_t value) : type(Jago::Type::BYTE), value(value) {
        }

        explicit JagoValue(const int16_t value) : type(Jago::Type::SHORT), value(value) {
        }

        explicit JagoValue(const float value) : type(Jago::Type::FLOAT), value(value) {
        }

        explicit JagoValue(const double value) : type(Jago::Type::DOUBLE), value(value) {
        }

        explicit JagoValue(const bool value) : type(Jago::Type::BOOLEAN), value(value) {
        }

        explicit JagoValue(const char value) : type(Jago::Type::CHAR), value(value) {
        }

        [[nodiscard]] std::string toString() const noexcept {
            if (std::holds_alternative<std::string>(value)) {
                return std::get<std::string>(value); // Dereference shared_ptr
            }
            return this->asString(); // Return direct string
        }

        [[nodiscard]] int32_t toInt() const noexcept {
            return std::get<int32_t>(value);
        }

        [[nodiscard]] int64_t toLong() const noexcept {
            return std::get<int64_t>(value);
        }

        [[nodiscard]] int8_t toByte() const noexcept {
            return static_cast<int8_t>(std::get<int32_t>(value));
        }

        [[nodiscard]] uint8_t toChar() const noexcept {
            return static_cast<uint8_t>(std::get<int8_t>(value));
        }

        [[nodiscard]] int16_t toShort() const noexcept {
            return static_cast<int16_t>(std::get<int32_t>(value));
        }

        [[nodiscard]] float toFloat() const noexcept {
            return std::get<float>(value);
        }

        [[nodiscard]] double toDouble() const noexcept {
            return std::get<double>(value);
        }

        [[nodiscard]] bool toBool() const noexcept {
            return std::get<bool>(value);
        }

        [[nodiscard]] std::string asString() const;
        [[nodiscard]] double asDouble() const;
        [[nodiscard]] int64_t asLong() const;
        [[nodiscard]] int32_t asInt() const;
        [[nodiscard]] JagoValue castToType(const JagoType& type) const;

        bool operator==(const JagoType& type) const {
            return this->type == type;
        }

        bool operator==(const JagoValue &other) const;
        bool operator>(const JagoValue &other) const;
        bool operator<(const JagoValue &other) const;
        bool operator>=(const JagoValue &other) const;
        bool operator<=(const JagoValue &other) const;

        JagoValue &operator=(int value);
        JagoValue &operator=(double value);
        JagoValue &operator=(float value);
        JagoValue &operator=(char value);
        JagoValue &operator=(const std::string &value);
        JagoValue &operator=(bool value);
        JagoValue &operator=(int64_t value);

        friend std::ostream& operator<<(std::ostream& out, const JagoValue& value);
    };

} // Jago

#endif //JAGOVALUE_H
