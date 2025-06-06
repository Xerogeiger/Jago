//
// Created by creep on 1/13/2025.
//

#include "StatementNodes.h"

#include "../JagoEvaluator.h"
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
        out << std::string(indent, '\t') << "AssignmentStatement: " << type << " " << variableName
            << std::endl;
        value->prettyPrint(out, indent + 1);
    }

    void MethodDeclarationStatement::accept(Visitor &visitor) {
        visitor.visit(std::move(*this));
    }

    void MethodDeclarationStatement::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "MethodStatement: " << name << std::endl;
        out << std::string(indent, '\t') << "Return Type: " << returnType.getTypeName() << std::endl;
        out << std::string(indent, '\t') << "Parameters: " << std::endl;
        for (const auto &param: parameters) {
            out << std::string(indent, '\t') << "Name: " << param.name << " Type: " << param.type.getTypeName()
                << std::endl;
        }
        out << std::string(indent, '\t') << "Body: " << std::endl;
        body->prettyPrint(out, indent + 1);
    }

    void ScopeBody::accept(Visitor &visitor) {
        for (auto &statement: statements) {
            statement->accept(visitor);
        }
    }

    void ScopeBody::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "ScopeBody: " << std::endl;
        for (const auto &statement: statements) {
            statement->prettyPrint(out, indent + 1);
        }
    }
    void IfStatement::accept(Visitor &visitor) {
        visitor.visit(*this);
    }

    void IfStatement::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "IfStatement: " << std::endl;
        condition->prettyPrint(out, indent + 1);
        out << std::string(indent, '\t') << "Body: " << std::endl;
        trueCase->prettyPrint(out, indent + 1);
        if (falseCase) {
            out << std::string(indent, '\t') << "Else Body: " << std::endl;
            falseCase->prettyPrint(out, indent + 1);
        }
    }
    void IncrementalForStatement::accept(Visitor &visitor) {
        visitor.visit(*this);
    }
    void IncrementalForStatement::prettyPrint(std::ostream &out, int indent) const {
        std::cout << std::string(indent, '\t') << "IncrementalForStatement: " << std::endl;
        std::cout << std::string(indent, '\t') << "Initialization: " << std::endl;
        initialization->prettyPrint(out, indent + 1);
        std::cout << std::string(indent, '\t') << "Condition: " << std::endl;
        condition->prettyPrint(out, indent + 1);
        std::cout << std::string(indent, '\t') << "Increment: " << std::endl;
        increment->prettyPrint(out, indent + 1);
        std::cout << std::string(indent, '\t') << "Body: " << std::endl;
        body->prettyPrint(out, indent + 1);
    }
    void ContinueStatement::accept(Visitor &visitor) { visitor.visit(*this); }

    void ClassDeclarationStatement::accept(Visitor &visitor) { visitor.visit(*this); }
    void ClassDeclarationStatement::prettyPrint(std::ostream &out, int indent) const {
        out << std::string(indent, '\t') << "ClassDeclarationStatement: " << this->name << std::endl;
        out << std::string(indent, '\t') << "Members: " << std::endl;
        for (const auto &member: methods) {
            out << std::string(indent, '\t') << "Member: " << member->getName() << std::endl;
        }
    }
} // namespace Jago
