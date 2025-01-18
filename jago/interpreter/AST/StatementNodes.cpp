//
// Created by creep on 1/13/2025.
//

#include "StatementNodes.h"

#include "Visitor.h"

namespace Jago {
    void ReturnStatement::accept(Visitor& visitor) {
        visitor.visit(*this);
    }

    void ReturnStatement::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "ReturnStatement: " << std::endl;
        value->prettyPrint(out, indent + 1);
    }

    void AssignmentStatement::accept(Visitor &visitor) {
        visitor.visit(*this);
    }

    void AssignmentStatement::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "AssignmentStatement: " << type << " " << variableName << std::endl;
        value->prettyPrint(out, indent + 1);
    }
}
