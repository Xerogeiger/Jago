//
// Created by creep on 2/20/2025.
//

#ifndef JAGOTYPE_H
#define JAGOTYPE_H
#include "../PrimitiveTypes.h"
#include <memory>

class JagoClass;

namespace Jago {
    class JagoType {
    private:
        std::string typeName;
        std::string alias;
        std::shared_ptr<JagoClass> classType = nullptr; // Class type for non-primitive types
        // Primitive types are: int, float, bool, char, long, double, byte, short
        bool isPrimitive;

    public:
        explicit JagoType(std::string_view typeName, std::string_view alias, bool isPrimitive)
            : typeName(typeName), alias(alias), isPrimitive(isPrimitive) {
        }

        [[nodiscard]] std::string getTypeName() const {
            return typeName;
        }

        [[nodiscard]] std::string getAlias() const {
            return alias;
        }

        [[nodiscard]] bool getIsPrimitive() const {
            return isPrimitive;
        };

        bool operator==(const JagoType &otherType) const {
            return this->typeName == otherType.typeName;
        }
    };

    namespace Type {
        inline JagoType INT("int", "I", true);
        inline JagoType FLOAT("float", "F", true);
        inline JagoType BOOLEAN("bool", "Z", true);
        inline JagoType STRING("string", "E", false);
        inline JagoType CHAR("char", "C", true);
        inline JagoType LONG("long", "J", true);
        inline JagoType DOUBLE("double", "D", true);
        inline JagoType BYTE("byte", "B", true);
        inline JagoType SHORT("short", "S", true);
        inline JagoType VOID("void", "V", true);
        inline JagoType OBJECT("object", "LObject;", false);
    }

    inline JagoType getTypeFromString(std::string typeName) {
        if (Jago::Type::INT.getTypeName() == typeName) {
            return Jago::Type::INT;
        } else if (Type::FLOAT.getTypeName() == typeName) {
            return Type::FLOAT;
        } else if (Type::BOOLEAN.getTypeName() == typeName) {
            return Type::BOOLEAN;
        } else if (Type::STRING.getTypeName() == typeName) {
            return Type::STRING;
        } else if (Type::CHAR.getTypeName() == typeName) {
            return Type::CHAR;
        } else if (Type::LONG.getTypeName() == typeName) {
            return Type::LONG;
        } else if (Type::DOUBLE.getTypeName() == typeName) {
            return Type::DOUBLE;
        } else if (Type::BYTE.getTypeName() == typeName) {
            return Type::BYTE;
        } else if (Type::SHORT.getTypeName() == typeName) {
            return Type::SHORT;
        } else if (Type::VOID.getTypeName() == typeName) {
            return Type::VOID;
        } else {
            return Type::OBJECT;
        }
    }
}
#endif //JAGOTYPE_H
