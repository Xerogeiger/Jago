#include <iostream>

#include "jago/JagoUtils.h"
#include "jago/JagoLexer.h"
#include "jago/JagoParser.h"
#include "jago/interpreter/JagoInterpreter.h"

using namespace Jago;

int main() {
    std::string testString = "int var = 4 ** 3;";

    JagoLexer lexer;
    JagoParser parser;
    JagoInterpreter interpreter;

    interpreter.Interpret(parser.Parse(lexer.Lex(testString)));

    return 0;
}
