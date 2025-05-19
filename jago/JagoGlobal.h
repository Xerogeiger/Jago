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

    [[maybe_unused]] const Operator::JagoOperator ParenthesisOpenOperator = Operator::JagoOperator{"(", Operator::OperatorType::ParenthesisOpen,
                                                                               Operator::OperatorUsage::EitherSideUnary, 100};
    [[maybe_unused]] const Operator::JagoOperator ParenthesisCloseOperator = Operator::JagoOperator{")", Operator::OperatorType::ParenthesisClose,
                                                                                Operator::OperatorUsage::EitherSideUnary, 100};

    [[maybe_unused]] const std::vector<Operator::JagoOperator> DefaultJagoOperators = {
            Operator::JagoOperator{"=", Operator::OperatorType::Assignment, Operator::OperatorUsage::Binary, 1},
            Operator::JagoOperator{"+=", Operator::OperatorType::AdditionAssignment, Operator::OperatorUsage::Binary, 1},
            Operator::JagoOperator{"-=", Operator::OperatorType::SubtractionAssignment, Operator::OperatorUsage::Binary, 1},
            Operator::JagoOperator{"*=", Operator::OperatorType::MultiplicationAssigment, Operator::OperatorUsage::Binary, 1},
            Operator::JagoOperator{"/=", Operator::OperatorType::DivisionAssignment, Operator::OperatorUsage::Binary, 1},
            Operator::JagoOperator{"%=", Operator::OperatorType::ModulusAssignment, Operator::OperatorUsage::Binary, 1},
            Operator::JagoOperator{"**=", Operator::OperatorType::PowerOfAssignment, Operator::OperatorUsage::Binary, 1},

            Operator::JagoOperator{"||", Operator::OperatorType::LogicalOr, Operator::OperatorUsage::Binary, 3},

            Operator::JagoOperator{"&&", Operator::OperatorType::LogicalAnd, Operator::OperatorUsage::Binary, 4},

            Operator::JagoOperator{"|", Operator::OperatorType::BitwiseOr, Operator::OperatorUsage::Binary, 5},

            Operator::JagoOperator{"^", Operator::OperatorType::BitwiseXor, Operator::OperatorUsage::Binary, 6},

            Operator::JagoOperator{"&", Operator::OperatorType::BitwiseAnd, Operator::OperatorUsage::Binary, 7},

            Operator::JagoOperator{"==", Operator::OperatorType::EqualTo, Operator::OperatorUsage::Binary, 8},
            Operator::JagoOperator{"!=", Operator::OperatorType::NotEqualTo, Operator::OperatorUsage::Binary, 8},

            Operator::JagoOperator{"<", Operator::OperatorType::LessThan, Operator::OperatorUsage::Binary, 9},
            Operator::JagoOperator{"<=", Operator::OperatorType::LessThanOrEqualTo, Operator::OperatorUsage::Binary, 9},
            Operator::JagoOperator{">", Operator::OperatorType::GreaterThan, Operator::OperatorUsage::Binary, 9},
            Operator::JagoOperator{">=", Operator::OperatorType::GreaterThanOrEqualTo, Operator::OperatorUsage::Binary, 9},

            Operator::JagoOperator{"<<", Operator::OperatorType::BitwiseLeftShift, Operator::OperatorUsage::Binary, 10},
            Operator::JagoOperator{">>", Operator::OperatorType::BitwiseRightShiftWithSign, Operator::OperatorUsage::Binary, 10},
            Operator::JagoOperator{">>>", Operator::OperatorType::BitwiseRightShiftWithoutSign, Operator::OperatorUsage::Binary, 10},

            Operator::JagoOperator{"+", Operator::OperatorType::Addition, Operator::OperatorUsage::Binary, 11},
            Operator::JagoOperator{"-", Operator::OperatorType::Subtraction, Operator::OperatorUsage::Binary, 11},

            Operator::JagoOperator{"*", Operator::OperatorType::Multiplication, Operator::OperatorUsage::Binary, 12},
            Operator::JagoOperator{"/", Operator::OperatorType::Division, Operator::OperatorUsage::Binary, 12},
            Operator::JagoOperator{"%", Operator::OperatorType::Modulus, Operator::OperatorUsage::Binary, 12},

            Operator::JagoOperator{"**", Operator::OperatorType::PowerOf, Operator::OperatorUsage::Binary, 13},

            Operator::JagoOperator{"~", Operator::OperatorType::UnaryBitwiseComplement, Operator::OperatorUsage::LeftSideUnary, 14},
            Operator::JagoOperator{"!", Operator::OperatorType::UnaryLogicalNegation, Operator::OperatorUsage::LeftSideUnary, 14},
            Operator::JagoOperator{"++", Operator::OperatorType::UnaryPreIncrement, Operator::OperatorUsage::LeftSideUnary, 14},
            Operator::JagoOperator{"--", Operator::OperatorType::UnaryPreDecrement, Operator::OperatorUsage::LeftSideUnary, 14},
            Operator::JagoOperator{"-", Operator::OperatorType::UnaryMinus, Operator::OperatorUsage::LeftSideUnary, 14},
            Operator::JagoOperator{"+", Operator::OperatorType::UnaryPlus, Operator::OperatorUsage::LeftSideUnary, 14},

            Operator::JagoOperator{"++", Operator::OperatorType::UnaryPostIncrement, Operator::OperatorUsage::RightSideUnary, 15},
            Operator::JagoOperator{"--", Operator::OperatorType::UnaryPostDecrement, Operator::OperatorUsage::RightSideUnary, 15},

            Operator::JagoOperator{".", Operator::OperatorType::MemberSelection, Operator::OperatorUsage::Binary, 16}
    };

    [[maybe_unused]] const JagoKeyword *const NewObjectKeyword =
            new JagoKeyword("new", KeywordType::CreationDeclaration);

    [[maybe_unused]] const JagoKeyword *const PublicExpressionModifier =
            new JagoKeyword("public", KeywordType::ExpressionModifier);
    [[maybe_unused]] const JagoKeyword *const PrivateExpressionModifier =
            new JagoKeyword("private", KeywordType::ExpressionModifier);
    [[maybe_unused]] const JagoKeyword *const ProtectedExpressionModifier =
            new JagoKeyword("protected", KeywordType::ExpressionModifier);
    [[maybe_unused]] const JagoKeyword *const DefaultExpressionModifier =
            new JagoKeyword("default", KeywordType::ExpressionModifier);

    [[maybe_unused]] const JagoKeyword *const ForStatementKeyword =
            new JagoKeyword("for", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const IfStatementKeyword =
            new JagoKeyword("if", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const ElseStatementKeyword =
            new JagoKeyword("else", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const SwitchStatementKeyword =
            new JagoKeyword("switch", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const CaseStatementKeyword =
            new JagoKeyword("case", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const TryStatementKeyword =
            new JagoKeyword("try", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const CatchStatementKeyword =
            new JagoKeyword("catch", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const FinallyStatementKeyword =
            new JagoKeyword("finally", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const WhileStatementKeyword =
            new JagoKeyword("while", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const DoWhileStatementKeyword =
            new JagoKeyword("do", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const BreakStatementKeyword =
            new JagoKeyword("break", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const ContinueStatementKeyword =
            new JagoKeyword("continue", KeywordType::StatementDeclaration);
    [[maybe_unused]] const JagoKeyword *const ReturnStatementKeyword =
            new JagoKeyword("return", KeywordType::StatementDeclaration);

    [[maybe_unused]] const JagoKeyword *const ClassDeclarationKeyword =
            new JagoKeyword("class", KeywordType::TypeDeclaration);
    [[maybe_unused]] const JagoKeyword *const InterfaceDeclarationKeyword =
            new JagoKeyword("interface", KeywordType::TypeDeclaration);
    [[maybe_unused]] const JagoKeyword *const EnumDeclarationKeyword =
            new JagoKeyword("enum", KeywordType::TypeDeclaration);

    [[maybe_unused]] const JagoKeyword *const AbstractExpressionModifierKeyword =
            new JagoKeyword("abstract", KeywordType::ExpressionModifier);
    [[maybe_unused]] const JagoKeyword *const ConstExpressionModifierKeyword =
            new JagoKeyword("const", KeywordType::ExpressionModifier);
    [[maybe_unused]] const JagoKeyword *const StaticExpressionModifierKeyword =
            new JagoKeyword("static", KeywordType::ExpressionModifier);

    [[maybe_unused]] const JagoKeyword *const ImportDeclarationKeyword =
            new JagoKeyword("import", KeywordType::ImportDeclaration);

    [[maybe_unused]] const JagoKeyword *const PrimitiveInt =
            new JagoKeyword("int", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveLong =
            new JagoKeyword("long", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveShort =
            new JagoKeyword("short", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveByte =
            new JagoKeyword("byte", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveChar =
            new JagoKeyword("char", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveBoolean =
            new JagoKeyword("boolean", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveFloat =
            new JagoKeyword("float", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveDouble =
            new JagoKeyword("double", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveString =
            new JagoKeyword("string", KeywordType::PrimitiveType);
    [[maybe_unused]] const JagoKeyword *const PrimitiveVoid =
            new JagoKeyword("void", KeywordType::PrimitiveType);

    [[maybe_unused]] const JagoKeyword *const DefineFunctionKeyword =
            new JagoKeyword("define", KeywordType::CreationDeclaration);


    inline bool isPrimitiveType(std::string_view type) {
        return type == "int" || type == "long" || type == "short" || type == "byte" || type == "char" ||
               type == "boolean" || type == "float" || type == "double" || type == "void" || type == "string";
    }

    [[maybe_unused]] const std::vector<const JagoKeyword *> DefaultJagoKeywords{
        NewObjectKeyword,

        ForStatementKeyword,
        IfStatementKeyword,
        ElseStatementKeyword,
        SwitchStatementKeyword,
        CaseStatementKeyword,
        TryStatementKeyword,
        CatchStatementKeyword,
        FinallyStatementKeyword,
        WhileStatementKeyword,
        DoWhileStatementKeyword,
        BreakStatementKeyword,
        ContinueStatementKeyword,
        ReturnStatementKeyword,

        ClassDeclarationKeyword,
        InterfaceDeclarationKeyword,
        EnumDeclarationKeyword,

        AbstractExpressionModifierKeyword,
        ConstExpressionModifierKeyword,
        StaticExpressionModifierKeyword,

        PublicExpressionModifier,
        PrivateExpressionModifier,
        ProtectedExpressionModifier,
        DefaultExpressionModifier,

        ImportDeclarationKeyword,

        PrimitiveInt,
        PrimitiveLong,
        PrimitiveShort,
        PrimitiveByte,
        PrimitiveChar,
        PrimitiveBoolean,
        PrimitiveFloat,
        PrimitiveDouble,
        PrimitiveString,
        PrimitiveVoid,

        DefineFunctionKeyword
    };
}

#endif //JAGO_JAGOGLOBAL_H
