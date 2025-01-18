cmake_minimum_required(VERSION 3.20)
project(Jago)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(GoogleTests)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enabling extra warnings and sanitizers for Debug build.")

    # Common warning flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_executable(Jago main.cpp jago/JagoLexer.cpp jago/JagoLexer.h jago/JagoToken.cpp jago/JagoToken.h jago/JagoUtils.h jago/JagoUtils.cpp jago/JagoParser.cpp jago/JagoParser.h jago/JagoOperator.cpp jago/JagoOperator.h jago/JagoGlobal.h jago/JagoKeyword.cpp jago/JagoKeyword.h jago/compiler/JagoCompiler.cpp jago/compiler/JagoCompiler.h jago/JagoBytecodes.h jago/exceptions/JagoCompilerException.h jago/JagoExpressionFlag.h jago/PrimitiveTypes.h
        jago/interpreter/JagoInterpreter.cpp
        jago/interpreter/JagoInterpreter.h
        jago/interpreter/JagoScope.cpp
        jago/interpreter/JagoScope.h
        jago/interpreter/JagoMethod.cpp
        jago/interpreter/JagoMethod.h
        jago/interpreter/AST/ASTNode.cpp
        jago/interpreter/AST/ASTNode.h
        jago/interpreter/AST/Visitor.cpp
        jago/interpreter/AST/Visitor.h
        jago/interpreter/AST/StatementNodes.cpp
        jago/interpreter/AST/StatementNodes.h
        jago/interpreter/AST/ExpressionNodes.cpp
        jago/interpreter/AST/ExpressionNodes.h
        jago/interpreter/JagoEvaluator.cpp
        jago/interpreter/JagoEvaluator.h
        jago/interpreter/JagoValue.cpp
        jago/interpreter/JagoValue.h)
