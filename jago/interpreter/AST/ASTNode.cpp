//
// Created by creep on 1/13/2025.
//

#include "ASTNode.h"

#include "StatementNodes.h"

namespace Jago {
    void Program::accept(Visitor &visitor) {
        for (const auto &statement : statements) {
            statement->accept(visitor);
        }
    }

    void Program::prettyPrint(std::ostream &out, int indent) const {
        for (const auto &statement : statements) {
            statement->prettyPrint(out, indent);
            out << std::endl;
        }
    }
} // Jago