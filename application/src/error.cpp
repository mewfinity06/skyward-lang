#include "error.hpp"

Error::Error(ErrorKind kind, string message) : kind(kind), message(message) {}

Error::Error() : kind(ErrorKind::ErrorOkay), message("Okay") {}

void Error::print() const {
    if (is_okay()) { return; }
        
    std::cout << Error::error_translations.at(kind) << ": " << message << std::endl;
}

bool Error::is_okay() const {
    return kind == ErrorKind::ErrorOkay;
}

