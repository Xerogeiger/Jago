//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOTOKEN_H
#define JAGO_JAGOTOKEN_H

#include <cstdint>
#include <type_traits>
#include <string_view>
#include <iostream>

namespace Jago {
    namespace Token {
        enum JagoTokenType: uint8_t {
            Keyword,
            Name,
            ScopeOpen,
            ScopeClose,
            Operator,
            ParenthesisOpen,
            ParenthesisClose,
            IndexerOpen,
            IndexerClose,
            NumberLiteral,
            StringLiteral,
            CharacterLiteral,
            StatementEnd
        };
    }

    const char* const JagoTokenTypeNames[] = {"Keyword", "Name", "ScopeOpen", "ScopeClose", "Operator", "ParenthesisOpen",
                                        "ParenthesisClose", "IndexerOpen", "IndexerClose", "NumberLiteral",
                                        "StringLiteral", "CharacterLiteral", "StatementEnd"};

    struct JagoToken {
    public:
        Token::JagoTokenType TokenType;
        std::string TokenValue;
        int LineNumber;

        friend std::ostream& operator<< (std::ostream &out, const JagoToken& data);
    };

    std::ostream& operator<< (std::ostream &out, const JagoToken& data);
}

#endif //JAGO_JAGOTOKEN_H
