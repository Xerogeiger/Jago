//
// Created by creep on 12/13/2022.
//

#include "JagoParser.h"
#include "JagoToken.h"

namespace Jago {
    [[maybe_unused]] std::vector<JagoToken> Jago::JagoParser::Parse(const std::vector<std::string_view>& lexedStrings) {
        ParserSettings settings = this->parserSettings;

        int lineNumber = 1;

        std::string statementEndString;
        statementEndString.push_back(settings.statementEnd);

        std::vector<JagoToken> tokens;
        std::vector<const JagoKeyword*> keywords = settings.Keywords;
        std::vector<Operator::JagoOperator> operators = settings.Operators;

        for(auto token : lexedStrings) {
            if(token.length() == 0)
                continue;

            if(token.length() == 1) {
                char c = token[0];
                if(c == settings.lineSeparator) {
                    lineNumber++;
                    continue;
                } else if(c == '(') {
                    tokens.push_back(JagoToken{Token::JagoTokenType::ParenthesisOpen, "(", lineNumber});
                    continue;
                } else if(c == ')') {
                    tokens.push_back(JagoToken{Token::JagoTokenType::ParenthesisClose, ")", lineNumber});
                    continue;
                } else if(c == settings.statementEnd) {
                    tokens.push_back(JagoToken{Token::JagoTokenType::StatementEnd, statementEndString, lineNumber});
                    continue;
                }
            }

            if(StringEquals(token, settings.scopeOpen)) {
                tokens.push_back(JagoToken{Token::JagoTokenType::ScopeOpen, settings.scopeOpen, lineNumber});
            } else if(StringEquals(token, settings.scopeClose)) {
                tokens.push_back(JagoToken{Token::JagoTokenType::ScopeClose, settings.scopeClose, lineNumber});
            } else if(StringEquals(token, settings.indexerOpen)) {
                tokens.push_back(JagoToken{Token::JagoTokenType::IndexerOpen, settings.indexerOpen, lineNumber});
            } else if(StringEquals(token, settings.indexerClose)) {
                tokens.push_back(JagoToken{Token::JagoTokenType::IndexerClose, settings.indexerClose, lineNumber});
            } else { //The only available token types left is operator and keyword
                bool foundType = false;

                for(const auto& keyword : keywords) {
                    if(StringEquals(token, keyword->keywordName)) {
                        tokens.push_back(JagoToken{Token::JagoTokenType::Keyword, keyword->keywordName, lineNumber});
                        foundType = true;
                        break;
                    }
                }

                if(!foundType) {
                    for(const auto& op : operators) {
                        if(StringEquals(token, op.OperatorSymbol)) {
                            tokens.push_back(JagoToken{Token::JagoTokenType::Operator, op.OperatorSymbol, lineNumber});
                            foundType = true;
                            break;
                        }
                    }
                }

                if(!foundType) {
                    char firstCharacter = token[0];

                    if(firstCharacter == '\"') {
                        if(token[token.length()-1] != '\"') {
                            throw std::invalid_argument("Expected a string literal to both start and end with double quotes, error on line " + std::to_string(lineNumber));
                        }

                        tokens.push_back(JagoToken{Token::JagoTokenType::StringLiteral, std::string(token.substr(1, token.length() - 2)), lineNumber});
                    } else if(firstCharacter == '\'') {
                        if(token[token.length()-1] != '\'') {
                            throw std::invalid_argument("Expected a character literal to both start and end with single quotes, error on line " + std::to_string(lineNumber));
                        }

                        tokens.push_back(JagoToken{Token::JagoTokenType::CharacterLiteral, std::string(token.substr(1, token.length() - 2)), lineNumber});
                    } else if(IsNumber(firstCharacter)) {
                        tokens.push_back(JagoToken{Token::JagoTokenType::NumberLiteral, std::string(token), lineNumber});
                    } else {
                        tokens.push_back(JagoToken{Token::JagoTokenType::Name, std::string(token), lineNumber});
                    }
                }
            }
        }

        return tokens;
    }

    JagoParser::JagoParser() {
        this->parserSettings = ParserSettings {
            .Operators = DefaultJagoOperators,
            .Keywords = DefaultJagoKeywords,
            .lineSeparator = '\n',
            .statementEnd = ';',
            .scopeOpen = DefaultJagoScopeOpen,
            .scopeClose = DefaultJagoScopeClose,
            .indexerOpen = DefaultIndexerOpen,
            .indexerClose = DefaultIndexerClose,
        };
    }
}
