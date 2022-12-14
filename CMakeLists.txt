cmake_minimum_required(VERSION 3.20)
project(Jago)

set(CMAKE_CXX_STANDARD 23)

add_executable(Jago main.cpp jago/JagoLexer.cpp jago/JagoLexer.h jago/JagoToken.cpp jago/JagoToken.h jago/JagoUtils.h jago/JagoUtils.cpp jago/JagoParser.cpp jago/JagoParser.h jago/interpreter/JagoInterpreter.cpp jago/interpreter/JagoInterpreter.h jago/JagoOperator.cpp jago/JagoOperator.h jago/JagoGlobal.h jago/JagoKeyword.cpp jago/JagoKeyword.h jago/JagoCompiler.cpp jago/JagoCompiler.h jago/JagoBytecodes.h jago/interpreter/JagoScope.cpp jago/interpreter/JagoScope.h jago/interpreter/JagoVariable.cpp jago/interpreter/JagoVariable.h jago/interpreter/JagoMethod.cpp jago/interpreter/JagoMethod.h jago/interpreter/JagoType.cpp jago/interpreter/JagoType.h jago/interpreter/JagoField.cpp jago/interpreter/JagoField.h jago/interpreter/JagoNativeMethod.cpp jago/interpreter/JagoNativeMethod.h jago/interpreter/JagoType.fwd.h)
