//
// Created by creep on 1/13/2025.
//

#include "ExpressionNodes.h"
#include "Visitor.h"

namespace Jago {
    void Literal::accept(Visitor& visitor) {
        visitor.visit(*this);
    }

    void Literal::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "Literal: " << value << std::endl;
    }
    void Variable::accept(Visitor &visitor) { visitor.visit(*this); }
    void Variable::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "Variable: " << name << std::endl;
    }

    void BinaryExpression::accept(Visitor& visitor) {
        visitor.visit(*this);
    }

    void BinaryExpression::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "BinaryExpression: " << op << std::endl;
        left->prettyPrint(out, indent + 1);
        right->prettyPrint(out, indent + 1);
    }

    void UnaryExpression::accept(Visitor &visitor) {
        visitor.visit(*this);
    }

    void UnaryExpression::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "UnaryExpression: " << op << std::endl;
        expression->prettyPrint(out, indent + 1);
    }
    void MethodCallExpression::accept(Visitor &visitor) {
        visitor.visit(*this);
    }

    void MethodCallExpression::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "MethodCallExpression: " << name << std::endl;
        out << std::string(indent, '\t') << "Arguments: " << arguments.size() << std::endl;
        for (const auto &arg: arguments) {
            arg->prettyPrint(out, indent + 1);
        }
    }
    void NewExpression::accept(Visitor &visitor) { visitor.visit(*this); }
    void NewExpression::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "NewExpression: " << name << std::endl;
        out << std::string(indent, '\t') << "Arguments: " << arguments.size() << std::endl;
        for (const auto &arg: arguments) {
            arg->prettyPrint(out, indent + 1);
        }
    }
} // namespace Jago
