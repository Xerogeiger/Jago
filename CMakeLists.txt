cmake_minimum_required(VERSION 3.20)
project(Jago)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(GoogleTests)

add_executable(Jago main.cpp jago/JagoLexer.cpp jago/JagoLexer.h jago/JagoToken.cpp jago/JagoToken.h jago/JagoUtils.h jago/JagoUtils.cpp jago/JagoParser.cpp jago/JagoParser.h jago/JagoOperator.cpp jago/JagoOperator.h jago/JagoGlobal.h jago/JagoKeyword.cpp jago/JagoKeyword.h jago/compiler/JagoCompiler.cpp jago/compiler/JagoCompiler.h jago/JagoBytecodes.h jago/exceptions/JagoCompilerException.h jago/JagoExpressionFlag.h jago/compiler/JagoType.h)
