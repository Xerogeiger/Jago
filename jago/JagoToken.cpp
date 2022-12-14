//
// Created by creep on 12/13/2022.
//

#include "JagoToken.h"

std::ostream &Jago::operator<<(std::ostream &out, const Jago::JagoToken &data) {
    out << "JagoToken{TokenType=\"" << Jago::JagoTokenTypeNames[data.TokenType] << "\", TokenValue=\"" << data.TokenValue <<
    "\", LineNumber=" << data.LineNumber << "}";

    return out;
}
