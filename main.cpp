#include <iostream>

#include "jago/JagoUtils.h"
#include "jago/JagoLexer.h"
#include "jago/JagoParser.h"
#include "jago/compiler/JagoCompiler.h"
#include "jago/interpreter/JagoEvaluator.h"
#include "jago/interpreter/JagoInterpreter.h"

using namespace Jago;

int main() {
    std::string testString = "int var = 4 * 5;";

    JagoLexer lexer;
    JagoParser parser;

    auto tokens = parser.Parse(lexer.Lex(testString));

    JagoInterpreter interpreter;
    auto program = interpreter.interpret(tokens);

    program->prettyPrint(std::cout, 0);

    JagoEvaluator evaluator;

    program->accept(evaluator);

    std::cout << testString << std::endl;

    return 0;
}
