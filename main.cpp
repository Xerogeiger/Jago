#include "jago/JagoLexer.h"
#include "jago/JagoParser.h"
#include "jago/compiler/JagoCompiler.h"
#include "jago/interpreter/JagoEvaluator.h"
#include "jago/interpreter/JagoInterpreter.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Jago;

std::string ReadFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary); // Open file in binary mode to handle all data types.

    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Use a string stream to store file content
    std::ostringstream content;
    content << file.rdbuf(); // Reading the whole file buffer into the stream

    file.close();
    return content.str(); // Return the string with all file content
}

int main() {
    //Read the file in as a string
    std::string code = ReadFile("../test.jago");

    JagoLexer lexer;
    JagoParser parser;

    auto tokens = parser.Parse(lexer.Lex(code));

    for (const auto &token: tokens) {
        std::cout << token << std::endl;
    }

    JagoInterpreter interpreter;
    auto program = interpreter.interpret(tokens);

    program->prettyPrint(std::cout, 0);

    JagoEvaluator evaluator;

    program->accept(evaluator);

    evaluator.dump(std::cout);

    return 0;
}
