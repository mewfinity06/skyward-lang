#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <iostream>


typedef std::string string;
typedef unsigned char byte;

class Error {
    string message;
    enum ErrorKind {
        ERROR_NONE = 0,
        ERROR_TODO,
        ERROR_SYNTAX,
        ERROR_NOT_BOUND,
        ERROR_ARGUMENTS,
        ERROR_TYPE,
        ERROR_MEMORY,
        ERROR_FILE,
        ERROR_GENERIC,
    } kind;

    Error(ErrorKind kind, string message) : kind(kind), message(message) {}
    Error() : kind(ERROR_NONE), message("") {}

    void print() {
        std::cout << "Error!" << std::endl;
        switch (kind) {
            case ERROR_TODO: std::cout << "     | Todo"   << std::endl; break;
            case ERROR_SYNTAX: std::cout << "     | Syntax" << std::endl; break;
            case ERROR_NOT_BOUND: std::cout << "     | Not Bound" << std::endl; break;
            case ERROR_ARGUMENTS: std::cout << "     | ARGUMENTS" << std::endl; break;
            case ERROR_TYPE: std::cout << "     | Type" << std::endl; break;
            case ERROR_MEMORY: std::cout << "     | Memory" << std::endl; break;
            case ERROR_FILE: std::cout << "     | File" << std::endl; break;
            case ERROR_NONE:
            case ERROR_GENERIC:
                break;
            default: return;
        }
        if (message != "") {
            std::cout << "     ` " << message << std::endl;
        }
    }
};


#endif // TYPEDEFS_H_
