//
// Created by creep on 2/2/2023.
//

#ifndef JAGO_JAGOCOMPILEREXCEPTION_H
#define JAGO_JAGOCOMPILEREXCEPTION_H

#include <exception>
#include <string>
#include <string_view>

namespace Jago {
    class JagoCompilerException: std::exception {
    private:
        const char* message;
    public:
        [[maybe_unused]] explicit JagoCompilerException(const std::string_view message) {
            char* copiedString = new char[message.length()];

            message.copy(copiedString, message.length());

            this->message = copiedString;
        }

        [[maybe_unused]] explicit JagoCompilerException(const std::string& message) {
            this->message = message.c_str();
        }

        [[maybe_unused]] explicit JagoCompilerException(const char* message) {
            this->message = message;
        }

        [[nodiscard]] const char* what() const noexcept override { return message; }
    };
}

#endif //JAGO_JAGOCOMPILEREXCEPTION_H
