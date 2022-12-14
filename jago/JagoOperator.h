//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOOPERATOR_H
#define JAGO_JAGOOPERATOR_H

#include <string>

enum OperatorType {
    //Unary Operators (Single-Sided)

    //Precedence 100
    ParenthesisOpen,
    ParenthesisClose,

    //Precedence 16
    MemberSelection,

    //Precedence 15
    UnaryPostIncrement,
    UnaryPostDecrement,

    //Precedence 14
    UnaryPreIncrement,
    UnaryPreDecrement,
    UnaryPlus,
    UnaryMinus,
    UnaryLogicalNegation,
    UnaryBitwiseComplement,
    UnaryTypeCast,

    //Binary Operators (Two-Sided)

    //Precedence 13
    PowerOf,

    //Precedence 12
    Multiplication,
    Division,
    Modulus,

    //Precedence 11
    Addition,
    Subtraction,

    //Precedence 10
    BitwiseLeftShift,
    BitwiseRightShiftWithSign,
    BitwiseRightShiftWithoutSign,

    //Precedence 9
    LessThan,
    LessThanOrEqualTo,
    GreaterThan,
    GreaterThanOrEqualTo,

    //Precedence 8
    EqualTo,
    NotEqualTo,

    //Precedence 7
    BitwiseAnd,

    //Precedence 6
    BitwiseXor,

    //Precedence 5
    BitwiseOr,

    //Precedence 4
    LogicalAnd,

    //Precedence 3
    LogicalOr,

    //Precedence 2 (Unused, Reserved for ternary)

    //Precedence 1
    Assignment,
    AdditionAssignment,
    SubtractionAssignment,
    MultiplicationAssigment,
    DivisionAssignment,
    ModulusAssignment,
    PowerOfAssignment
};

enum OperatorUsage: int8_t {
    LeftSideUnary = 1,
    RightSideUnary = 2,
    EitherSideUnary = 3,
    Binary = 4
};

struct JagoOperator {
public:
    std::string OperatorSymbol;
    OperatorType OperatorType;
    OperatorUsage OperatorUsage;
    int Precedence;
};

#endif //JAGO_JAGOOPERATOR_H
