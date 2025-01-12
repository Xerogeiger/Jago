#include <iostream>

#include "jago/JagoUtils.h"
#include "jago/JagoLexer.h"
#include "jago/JagoParser.h"
#include "jago/compiler/JagoCompiler.h"

using namespace Jago;

int main() {
    std::string testString = "int var = 4 * 5;";

    JagoLexer lexer;
    JagoParser parser;

    auto tokens = parser.Parse(lexer.Lex(testString));

    JagoCompiler compiler;

    try {
        for (auto &byteCode: compiler.Compile(tokens)) {
            std::cout << (int) byteCode << std::endl;
        }
    } catch (Jago::JagoCompilerException& exception) {
        std::cerr << "Compiler Exception: " << exception.what() << std::endl;
    }

    return 0;
}
