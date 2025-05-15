//
// Created by creep on 1/12/2025.
//

#ifndef JAGOINTERPRETER_H
#define JAGOINTERPRETER_H
#include <vector>

#include "../JagoToken.h"
#include "AST/ASTNode.h"
#include "AST/ExpressionNodes.h"
#include "AST/StatementNodes.h"

namespace Jago {

    class JagoInterpreter {
    public:
        JagoInterpreter() = default;

        [[nodiscard]] ASTNode* interpret(std::vector<Jago::JagoToken> tokens) const;
        [[nodiscard]] std::unique_ptr<Statement> interpretStatement(std::vector<Jago::JagoToken> tokens, int& index) const;
        [[nodiscard]] static std::unique_ptr<Expression> interpretExpression(std::vector<Jago::JagoToken> tokens, int& index);
    };

} // Jago

#endif //JAGOINTERPRETER_H
