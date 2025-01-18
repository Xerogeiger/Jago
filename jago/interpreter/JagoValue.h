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

namespace Jago {

    class JagoValue {
    public:
        Jago::PrimitiveTypes type;

        std::variant<int32_t, int64_t, int8_t, int16_t, char, float, double, bool, std::string, std::shared_ptr<std::string>> value;

        JagoValue() : type(Jago::PrimitiveTypes::VOID), value(nullptr) {
        }

        // Constructor for std::string*
        JagoValue(const Jago::PrimitiveTypes type, std::string& value) : type(type) {
            this->value = std::make_shared<std::string>(value);
        }

        // Constructor for int32_t
        JagoValue(const Jago::PrimitiveTypes type, const int32_t value) : type(type) {
            this->value = value;
        }

        // Constructor for int64_t
        JagoValue(const Jago::PrimitiveTypes type, const int64_t value) : type(type) {
            this->value = value;
        }

        // Constructor for int8_t
        JagoValue(const Jago::PrimitiveTypes type, const int8_t value) : type(type) {
            this->value = value;
        }

        // Constructor for int16_t
        JagoValue(const Jago::PrimitiveTypes type, const int16_t value) : type(type) {
            this->value = value;
        }

        // Constructor for float
        JagoValue(const Jago::PrimitiveTypes type, const float value) : type(type) {
            this->value = value;
        }

        // Constructor for double
        JagoValue(const Jago::PrimitiveTypes type, const double value) : type(type) {
            this->value = value;
        }

        // Constructor for bool
        JagoValue(const Jago::PrimitiveTypes type, const bool value) : type(type) {
            this->value = value;
        }

        [[nodiscard]] std::string toString() const noexcept {
            if (std::holds_alternative<std::shared_ptr<std::string>>(value)) {
                return *std::get<std::shared_ptr<std::string>>(value); // Dereference shared_ptr
            }
            return std::get<std::string>(value); // Return direct string
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
        [[nodiscard]] JagoValue castToType(PrimitiveTypes type) const;

        bool operator==(const PrimitiveTypes type) const {
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
