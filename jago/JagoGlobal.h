//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOGLOBAL_H
#define JAGO_JAGOGLOBAL_H

#include <vector>
#include "JagoOperator.h"
#include "JagoKeyword.h"

namespace Jago {
    [[maybe_unused]] const std::string DefaultJagoScopeOpen = "{";
    [[maybe_unused]] const std::string DefaultJagoScopeClose = "}";
    [[maybe_unused]] const std::string DefaultIndexerOpen = "[";
    [[maybe_unused]] const std::string DefaultIndexerClose = "]";

    [[maybe_unused]] const JagoOperator ParenthesisOpenOperator = JagoOperator{"(", OperatorType::ParenthesisOpen, OperatorUsage::EitherSideUnary, 100};
    [[maybe_unused]] const JagoOperator ParenthesisCloseOperator = JagoOperator{")", OperatorType::ParenthesisClose, OperatorUsage::EitherSideUnary, 100};

    [[maybe_unused]] const std::vector<JagoOperator> DefaultJagoOperators = {
            JagoOperator{"=", OperatorType::Assignment, OperatorUsage::Binary, 1},
            JagoOperator{"+=", OperatorType::AdditionAssignment, OperatorUsage::Binary, 1},
            JagoOperator{"-=", OperatorType::SubtractionAssignment, OperatorUsage::Binary, 1},
            JagoOperator{"*=", OperatorType::MultiplicationAssigment, OperatorUsage::Binary, 1},
            JagoOperator{"/=", OperatorType::DivisionAssignment, OperatorUsage::Binary, 1},
            JagoOperator{"%=", OperatorType::ModulusAssignment, OperatorUsage::Binary, 1},
            JagoOperator{"**=", OperatorType::PowerOfAssignment, OperatorUsage::Binary, 1},

            JagoOperator{"||", OperatorType::LogicalOr, OperatorUsage::Binary, 3},

            JagoOperator{"&&", OperatorType::LogicalAnd, OperatorUsage::Binary, 4},

            JagoOperator{"|", OperatorType::BitwiseOr, OperatorUsage::Binary, 5},

            JagoOperator{"^", OperatorType::BitwiseXor, OperatorUsage::Binary, 6},

            JagoOperator{"&", OperatorType::BitwiseAnd, OperatorUsage::Binary, 7},

            JagoOperator{"==", OperatorType::EqualTo, OperatorUsage::Binary, 8},
            JagoOperator{"!=", OperatorType::NotEqualTo, OperatorUsage::Binary, 8},

            JagoOperator{"<", OperatorType::LessThan, OperatorUsage::Binary, 9},
            JagoOperator{"<=", OperatorType::LessThanOrEqualTo, OperatorUsage::Binary, 9},
            JagoOperator{">", OperatorType::GreaterThan, OperatorUsage::Binary, 9},
            JagoOperator{">=", OperatorType::GreaterThanOrEqualTo, OperatorUsage::Binary, 9},

            JagoOperator{"<<", OperatorType::BitwiseLeftShift, OperatorUsage::Binary, 10},
            JagoOperator{">>", OperatorType::BitwiseRightShiftWithSign, OperatorUsage::Binary, 10},
            JagoOperator{">>>", OperatorType::BitwiseRightShiftWithoutSign, OperatorUsage::Binary, 10},

            JagoOperator{"+", OperatorType::Addition, OperatorUsage::Binary, 11},
            JagoOperator{"-", OperatorType::Subtraction, OperatorUsage::Binary, 11},

            JagoOperator{"*", OperatorType::Multiplication, OperatorUsage::Binary, 12},
            JagoOperator{"/", OperatorType::Division, OperatorUsage::Binary, 12},
            JagoOperator{"%", OperatorType::Modulus, OperatorUsage::Binary, 12},

            JagoOperator{"**", OperatorType::PowerOf, OperatorUsage::Binary, 13},

            JagoOperator{"~", OperatorType::UnaryBitwiseComplement, OperatorUsage::LeftSideUnary, 14},
            JagoOperator{"!", OperatorType::UnaryLogicalNegation, OperatorUsage::LeftSideUnary, 14},
            JagoOperator{"++", OperatorType::UnaryPreIncrement, OperatorUsage::LeftSideUnary, 14},
            JagoOperator{"--", OperatorType::UnaryPreDecrement, OperatorUsage::LeftSideUnary, 14},
            JagoOperator{"-", OperatorType::UnaryMinus, OperatorUsage::LeftSideUnary, 14},
            JagoOperator{"+", OperatorType::UnaryPlus, OperatorUsage::LeftSideUnary, 14},

            JagoOperator{"++", OperatorType::UnaryPostIncrement, OperatorUsage::RightSideUnary, 15},
            JagoOperator{"--", OperatorType::UnaryPostDecrement, OperatorUsage::RightSideUnary, 15},

            JagoOperator{".", OperatorType::MemberSelection, OperatorUsage::Binary, 16}
    };

    [[maybe_unused]] const JagoKeyword* const NewObjectKeyword =
            new JagoKeyword("new", KeywordType::CreationDeclaration);

    [[maybe_unused]] const JagoKeyword* const PublicVisibilityModifier =
            new JagoKeyword("public", KeywordType::VisibilityModifier);
    [[maybe_unused]] const JagoKeyword* const PrivateVisibilityModifier =
            new JagoKeyword("private", KeywordType::VisibilityModifier);
    [[maybe_unused]] const JagoKeyword* const ProtectedVisibilityModifier =
            new JagoKeyword("protected", KeywordType::VisibilityModifier);
    [[maybe_unused]] const JagoKeyword* const DefaultVisibilityModifier =
            new JagoKeyword("default", KeywordType::VisibilityModifier);

    [[maybe_unused]] const JagoKeyword* const ForStatementKeyword =
            new JagoKeyword("for", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword* const IfStatementKeyword =
            new JagoKeyword("if", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword* const ElseStatementKeyword =
            new JagoKeyword("else", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword* const SwitchStatementKeyword =
            new JagoKeyword("switch", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword* const CaseStatementKeyword =
            new JagoKeyword("case", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword* const TryStatementKeyword =
            new JagoKeyword("try", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword* const CatchStatementKeyword =
            new JagoKeyword("catch", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword* const FinallyStatementKeyword =
            new JagoKeyword("finally", KeywordType::StatementDeclaration);

    [[maybe_unused]] const JagoKeyword* const ClassDeclarationKeyword =
            new JagoKeyword("class", KeywordType::TypeDeclaration);
    [[maybe_unused]] const JagoKeyword* const InterfaceDeclarationKeyword =
            new JagoKeyword("interface", KeywordType::TypeDeclaration);
    [[maybe_unused]] const JagoKeyword* const EnumDeclarationKeyword =
            new JagoKeyword("enum", KeywordType::TypeDeclaration);

    [[maybe_unused]] const JagoKeyword* const AbstractDeclarationModifierKeyword =
            new JagoKeyword("abstract", KeywordType::DeclarationModifier);
    [[maybe_unused]] const JagoKeyword* const ConstDeclarationModifierKeyword =
            new JagoKeyword("const", KeywordType::DeclarationModifier);
    [[maybe_unused]] const JagoKeyword* const StaticDeclarationModifierKeyword =
            new JagoKeyword("static", KeywordType::DeclarationModifier);

    [[maybe_unused]] const JagoKeyword* const ImportDeclarationKeyword =
            new JagoKeyword("import", KeywordType::ImportDeclaration);

    [[maybe_unused]] const std::vector<const JagoKeyword*> DefaultJagoKeywords {
            NewObjectKeyword,

            ForStatementKeyword,
            IfStatementKeyword,
            ElseStatementKeyword,
            SwitchStatementKeyword,
            CaseStatementKeyword,
            TryStatementKeyword,
            CatchStatementKeyword,
            FinallyStatementKeyword,

            ClassDeclarationKeyword,
            InterfaceDeclarationKeyword,
            EnumDeclarationKeyword,

            AbstractDeclarationModifierKeyword,
            ConstDeclarationModifierKeyword,
            StaticDeclarationModifierKeyword,

            PublicVisibilityModifier,
            PrivateVisibilityModifier,
            ProtectedVisibilityModifier,
            DefaultVisibilityModifier,

            ImportDeclarationKeyword
    };
}

#endif //JAGO_JAGOGLOBAL_H
