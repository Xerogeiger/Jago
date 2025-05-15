//
// Created by creep on 2/20/2025.
//

#ifndef JAGOTYPE_H
#define JAGOTYPE_H
#include "../PrimitiveTypes.h"

namespace Jago {
    class JagoType {
    private:
        std::string typeName;
        std::string alias;
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
}
#endif //JAGOTYPE_H
