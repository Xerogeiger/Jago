//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOKEYWORD_H
#define JAGO_JAGOKEYWORD_H

#include <string>

namespace Jago {
    enum KeywordType {
        VisibilityModifier,
        CreationDeclaration,
        TypeDeclaration,
        StatementDeclaration,
        ImportDeclaration,
        DeclarationModifier
    };

    class JagoKeyword {
    public:
        std::string keywordName;
        KeywordType keywordType;

        [[maybe_unused]] explicit JagoKeyword(const std::string& keywordName, KeywordType type);
    };
}


#endif //JAGO_JAGOKEYWORD_H
