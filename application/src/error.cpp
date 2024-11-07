#include "error.hpp"


Error::Error(ErrorKind kind, string message) : kind(kind), message(message) {}

Error::Error() : kind(ErrorKind::ErrorOkay), message("Okay") {}

void Error::print() {
    if (kind == ErrorKind::ErrorOkay) { return; }
    
    std::cout << Error::error_translations.at(kind) << ": " << message << std::endl;
}

bool Error::is_okay() {
    if (kind == ErrorKind::ErrorOkay) { return true; }
    return false;
}

