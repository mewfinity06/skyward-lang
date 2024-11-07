#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>
#include <optional>

typedef std::string string;

class Error {
public:
    enum ErrorKind {
        ErrorOkay,
        ErrorAssert,
        ErrorTodo,
        ErrorSyntax,
        ErrorNotBound,
        ErrorArgs,
        ErrorType,
        ErrorMemory,
        ErrorFile,
        ErrorGeneric,
    } kind;
    string message;
public:
    Error(ErrorKind kind, string message);
    Error();

    void print();
    bool is_okay();
};

#endif // ERROR_H_

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#ifdef ERROR_IMPL_

Error::Error(ErrorKind kind, string message) : kind(kind), message(message) {}
Error::Error() : kind(ErrorOkay), message("Okay") {}

void Error::print() {
    if (kind == ErrorOkay) { return; }
    switch (kind) {
    case ErrorGeneric:  std::cout << "Error";           break;
    case ErrorAssert:   std::cout << "Assertion Error"; break;
    case ErrorTodo:     std::cout << "Todo";            break;
    case ErrorSyntax:   std::cout << "Syntax Error";    break;
    case ErrorNotBound: std::cout << "Not Bound Error"; break;
    case ErrorArgs:     std::cout << "Argument Error";  break;
    case ErrorType:     std::cout << "Type Error";      break;
    case ErrorMemory:   std::cout << "Memory Error";    break;
    case ErrorFile:     std::cout << "File Error";      break;
    default:            std::cout << "Unknown error.";  return;
    }
    std::cout << ": " << message << std::endl;
}

bool Error::is_okay() {
    if (kind == ErrorOkay) { return true; }
    return false;
}

#endif