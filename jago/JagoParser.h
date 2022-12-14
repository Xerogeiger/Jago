//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOPARSER_H
#define JAGO_JAGOPARSER_H

#include <vector>
#include "JagoUtils.h"
#include "JagoGlobal.h"
#include "JagoToken.h"

namespace Jago {
    struct ParserSettings {
    public:
        std::vector<JagoOperator> Operators;
        std::vector<const JagoKeyword*> Keywords;

        char lineSeparator;
        char statementEnd;

        std::string scopeOpen;
        std::string scopeClose;

        std::string indexerOpen;
        std::string indexerClose;
    };

    class JagoParser {
    protected:
        ParserSettings parserSettings;
    public:
        JagoParser();

        [[maybe_unused]] std::vector<JagoToken> Parse(const std::vector<std::string_view>& lexedStrings);
    };
}

#endif //JAGO_JAGOPARSER_H
