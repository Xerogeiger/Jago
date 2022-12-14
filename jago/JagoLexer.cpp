//
// Created by creep on 12/13/2022.
//

#include "JagoLexer.h"

#define AddWordToken(start, end) tokens.emplace_back(value.data() + start, end - start)

namespace Jago {
    JagoLexer::JagoLexer() {
        settings = LexerSettings {
            .allowedWordCharacters = CopyAndSort(DefaultJagoAllowedWordCharacters),
            .whitespaceCharacters = CopyAndSort(DefaultJagoWhiteSpace),
            .multiCharacterSymbols = DefaultJagoMultiCharacterSymbols,
            .lineEnding = DefaultJagoLineEnding,
            .commentSettings = {
                    .blockCommentStart = DefaultJagoBlockCommentStart,
                    .blockCommentEnd = DefaultJagoBlockCommentEnd,
                    .lineCommentStart = DefaultJagoLineCommentStart
            }
        };

        SortByLength(settings.multiCharacterSymbols);
    }

    JagoLexer::JagoLexer(LexerSettings& settings) {
        this->settings = settings;

        Char::QuickSort(settings.allowedWordCharacters);
        Char::QuickSort(settings.whitespaceCharacters);

        SortByLength(settings.multiCharacterSymbols);
    }

    JagoLexer::~JagoLexer() = default;

    [[maybe_unused]]
    std::vector<std::string_view> JagoLexer::Lex(const std::string &value, bool includeLineEndings) {
        std::vector<std::string_view> tokens;

        uint32_t wordStart = -1;

        LexerSettings& lexerSettings = this->settings;
        LexerCommentSettings& commentSettings = lexerSettings.commentSettings;

        for(uint32_t i = 0; i < value.length(); i++) {
            char c = value[i];
            if(IsSymbol(value, i, value.length(), commentSettings.lineCommentStart)) {
                if(wordStart != -1) {
                    AddWordToken(wordStart, i);
                    wordStart = -1;
                }

                i += commentSettings.lineCommentStart.length();

                for(; i < value.length(); i++){
                    if(value[i] == settings.lineEnding) {
                        //Add line ending to token list
                        if(includeLineEndings) {
                            tokens.emplace_back(value.data() + i, 1);
                        }
                        break;
                    }
                }
            } else if(IsSymbol(value, i, value.length(), commentSettings.blockCommentStart)) {
                if(wordStart != -1) {
                    AddWordToken(wordStart, i);
                    wordStart = -1;
                }

                i += commentSettings.blockCommentStart.length();

                for(; i < value.length(); i++){
                    if(IsSymbol(value, i, value.length(), commentSettings.blockCommentEnd)) {
                        break;
                    } else if(value[i] == settings.lineEnding) {
                        if(includeLineEndings) {
                            tokens.emplace_back(value.data() + i, 1);
                        }
                    }
                }

                i += commentSettings.blockCommentEnd.length() - 1;
            } else if(Contains(lexerSettings.allowedWordCharacters, c)) {
                if(wordStart == -1)
                    wordStart = i;
            } else if(Contains(lexerSettings.whitespaceCharacters, c)) {
                if(wordStart != -1) {
                    AddWordToken(wordStart, i);
                    wordStart = -1;
                }
            } else {
                if(wordStart != -1) {
                    AddWordToken(wordStart, i);
                    wordStart = -1;
                }

                bool isMultiCharacterSymbol = false;

                for(const std::string& op: settings.multiCharacterSymbols) {
                    if(IsSymbol(value, i, value.length(), op)) {
                        tokens.emplace_back(value.data() + i, op.length());
                        i += op.length()-1;
                        isMultiCharacterSymbol = true;
                        break;
                    }
                }

                if(!isMultiCharacterSymbol) {
                    if (lexerSettings.lineEnding != c || includeLineEndings) {
                        tokens.emplace_back(value.data() + i, 1);
                    }
                }
            }
        }

        if(wordStart != -1) {
            AddWordToken(wordStart, value.length());
        }

        return tokens;
    }

    std::vector<char> CopyAndSort(const std::string &s) {
        std::vector<char> characters = std::vector<char>(s.begin(), s.end());

        Char::QuickSort(characters);

        return characters;
    }
}
