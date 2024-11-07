#pragma once
#include <optional>
#include "common.hpp"



class Error {
public:
    enum class ErrorKind {
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

private:
    // Translates error kind to string
    const static inline std::unordered_map<Error::ErrorKind, string> error_translations = {
        {ErrorKind::ErrorGeneric, "Error"},
        {ErrorKind::ErrorAssert, "Assertion Error"},
        {ErrorKind::ErrorTodo, "Todo"},
        {ErrorKind::ErrorSyntax, "Syntax Error"},
        {ErrorKind::ErrorNotBound, "Not Bound Error"},
        {ErrorKind::ErrorArgs, "Argument Error"},
        {ErrorKind::ErrorType, "Type Error"},
        {ErrorKind::ErrorMemory, "Memory Error"},
        {ErrorKind::ErrorFile, "File Error"}
    };

public:
    Error(ErrorKind kind, string message);
    Error();

    void print();
    bool is_okay();
};


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

