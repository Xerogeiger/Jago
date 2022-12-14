//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOLEXER_H
#define JAGO_JAGOLEXER_H

#include <utility>
#include <vector>
#include <string>
#include <string_view>
#include <array>
#include <iostream>
#include <cstdlib>
#include "JagoToken.h"
#include "JagoLexer.h"
#include "JagoUtils.h"

#define DefaultJagoAllowedWordCharacters "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_"
#define DefaultJagoWhiteSpace " \t\b\u000B\r"
#define DefaultJagoBlockCommentStart "/*"
#define DefaultJagoBlockCommentEnd "*/"
#define DefaultJagoLineCommentStart "//"
#define DefaultJagoLineEnding '\n'
#define DefaultJagoMultiCharacterSymbols {"**", "||", "&&", "->", "<<", ">>", ">>>", "==", "++", "--", "+=", "-=", "*=", "/=", "**=", "&=", "|=", "^=", "::", "%=", ">=", "<="}

namespace Jago {
    struct LexerCommentSettings {
    public:
        std::string blockCommentStart = DefaultJagoBlockCommentStart;
        std::string blockCommentEnd = DefaultJagoBlockCommentEnd;
        std::string lineCommentStart = DefaultJagoLineCommentStart;
    };

    struct LexerSettings {
    public:
        std::vector<char> allowedWordCharacters;
        std::vector<char> whitespaceCharacters;
        std::vector<std::string> multiCharacterSymbols;

        char lineEnding;

        LexerCommentSettings commentSettings;
    };

    class JagoLexer {
    protected:
        LexerSettings settings;
    public:
        JagoLexer();
        JagoLexer(LexerSettings& settings);

        ~JagoLexer();

        [[maybe_unused]] std::vector<std::string_view> Lex(const std::string& value, bool includeLineEndings = true);
    };

    std::vector<char> CopyAndSort(const std::string& s);
}

#endif //JAGO_JAGOLEXER_H
