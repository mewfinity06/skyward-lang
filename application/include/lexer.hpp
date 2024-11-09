#pragma once
#include "common.hpp"
#include "error.hpp"
#include <cctype>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <variant>
#include <algorithm> 
#include <locale>

// Forward declarations
class Token;

const std::string single_char_delims = "!@#$%^&*()+-={}[]|\\:;\"\'<>,.?/`~";

const std::string comment_start = "//";

// TODO: 
//     | Impliment non_word_tokens instead of multi_char_tokens
//     | Better name?
const std::unordered_set<std::string> non_word_tokens = {
    // Assignment
    ":", "=", ":=", "+=", "-=", "*=", "/=", "%=", "|=", "~=",
    "&=", "&~=", "<<=", ">>=", "&&=", "||=",
    // Seperators
    "{", "}", "(", ")", "[", "]", ";", ",", 
    // Iterators
    "..<", "..=", 
    // Comparison
    "==", "!=", "<=", ">=", "<", ">", 
    // Logical operators
    "&&", "||", "!", "|", "~", "&", "&~", "<<", ">>", 
    // Arithmetic
    "+", "-", "*", "%", "++", "--", "**",
    // Arrows
    "=>", "->", "|>",
    // Misc
    "@", "#", "$", "^", ".", "`", "\\", "?"
};

const std::unordered_set<std::string> types = {
    "Int", "Float", "Char", "String", "Byte", "Bool",
    "Void", "None", "Enum", "Compact", "Loose", "Union",
    "Vector", "Matrix", "Error", "Complex", "Usize",
    "Isize"
};

const std::unordered_set<std::string> keywords = {
    "func", "private", "public", "struct", "switch",
    "return", "if", "else", "finally", "impl", "const", "mut",
    "defer", "break", "continue", "for", "while",
    "signed", "unsigned", "use", "as"
};

enum TokenKind {
    // Multichar tokens
    TOKEN_IDENT,
    TOKEN_INT,
    TOKEN_FLOAT, // TODO: Add support for floats

    TOKEN_KEYWORD,
    TOKEN_TYPE,

    TOKEN_STRING,
    TOKEN_CHAR,

    // Assignment tokens
    TOKEN_ASSIGNMENT,                     // =
    TOKEN_COLON,                          // :  | Used for typing 
    TOKEN_ASSIGNMENT_IMPLICIT,            // :=
    TOKEN_ASSIGNMENT_PLUS,                // +=
    TOKEN_ASSIGNMENT_MINUS,               // -=
    TOKEN_ASSIGNMENT_STAR,                // *=
    TOKEN_ASSIGNMENT_DIVIDE,              // /=
    TOKEN_ASSIGNMENT_MOD,                 // %=
    TOKEN_ASSIGNMENT_BITWISE_OR,          // |=
    TOKEN_ASSIGNMENT_BITWISE_AND,         // &=
    TOKEN_ASSIGNMENT_BITWISE_XOR,         // ~=
    TOKEN_ASSIGNMENT_BITWISE_AND_NOT,     // &~=
    TOKEN_ASSIGNMENT_BITWISE_SHIFT_LEFT,  // <<=
    TOKEN_ASSIGNMENT_BITWISE_SHIFT_RIGHT, // >>=
    TOKEN_ASSIGNMENT_CONDITIONAL_AND,     // &&= | a &&= b -> a = a && b
    TOKEN_ASSIGNMENT_CONDITIONAL_OR,      // ||= | a ||= b -> a = a || b 

    // Seperator tokens
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_OPEN_CURLY,
    TOKEN_CLOSE_CURLY,
    TOKEN_SEMI_COLON,
    TOKEN_COMMA,

    // Iterators
    TOKEN_TO_LESS,  // ..<
    TOKEN_TO_EQUAL, // ..=

    // Comparison
    TOKEN_EQUALS,         // ==
    TOKEN_NOT_EQUALS,     // !=
    TOKEN_GREATER_EQUALS, // >=
    TOKEN_LESSER_EQUALS,  // <=
    TOKEN_LEFT_ARROW,     // <
    TOKEN_RIGHT_ARROW,    // >

    // Logical operators
    TOKEN_AND,         // &&
    TOKEN_OR,          // ||
    TOKEN_BANG,        // !
    TOKEN_PIPE,        // |
    TOKEN_TILDA,       // ~
    TOKEN_AMPERSAND,   // &
    TOKEN_AND_NOT,     // &~
    TOKEN_SHIFT_LEFT,  // <<
    TOKEN_SHIFT_RIGHT, // >>

    // Binary Tokens
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_DIVIDE,
    TOKEN_MOD,
    TOKEN_PLUS_PLUS,
    TOKEN_MINUS_MINUS,
    TOKEN_STAR_STAR,

    // Arrows
    TOKEN_FAT_ARROW,  // =>
    TOKEN_THIN_ARROW, // ->
    TOKEN_PIPE_LINE,  // |> (Thanks Gleam!)

    // Single char tokens
    TOKEN_ABROSE,      // @
    TOKEN_POUND,       // #
    TOKEN_DOLLAR,      // $
    TOKEN_CARROT,      // ^
    TOKEN_FULL_STOP,   // .
    TOKEN_QUESTION,    // ?
    TOKEN_BACK_TICK,   // `
    TOKEN_BACK_SLASH,

    TOKEN_EOF,
    TOKEN_UNKNOWN,
};



// Checkers
bool can_convert_to_int(const string& str);

bool is_identifier(const string& str);

bool is_keyword(const string& str);

bool is_type(const string& str);

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

// token functions
string token_kind_to_string(TokenKind kind);

vector<Token> tokenize_with_positions(const std::string file_path);

class Token {
private:
    const static inline std::unordered_map<string, TokenKind> string_token_to_enum_dictionary = {
        {"=", TOKEN_ASSIGNMENT},
        {":", TOKEN_COLON},
        {":=", TOKEN_ASSIGNMENT_IMPLICIT},
        {"+=", TOKEN_ASSIGNMENT_PLUS},
        {"-=", TOKEN_ASSIGNMENT_MINUS},
        {"*=", TOKEN_ASSIGNMENT_STAR},
        {"/=", TOKEN_ASSIGNMENT_DIVIDE},
        {"%=", TOKEN_ASSIGNMENT_MOD},
        {"|=", TOKEN_ASSIGNMENT_BITWISE_OR},
        {"&=", TOKEN_ASSIGNMENT_BITWISE_AND},
        {"~=", TOKEN_ASSIGNMENT_BITWISE_XOR},
        {"&~=", TOKEN_ASSIGNMENT_BITWISE_AND_NOT},
        {"<<=", TOKEN_ASSIGNMENT_BITWISE_SHIFT_LEFT},
        {">>=", TOKEN_ASSIGNMENT_BITWISE_SHIFT_RIGHT},
        {"&&=", TOKEN_ASSIGNMENT_CONDITIONAL_AND},
        {"||=", TOKEN_ASSIGNMENT_CONDITIONAL_OR},

        {"(", TOKEN_OPEN_PAREN},
        {")", TOKEN_CLOSE_PAREN},
        {"[", TOKEN_OPEN_BRACKET},
        {"]", TOKEN_CLOSE_BRACKET},
        {"{", TOKEN_OPEN_CURLY},
        {"}", TOKEN_CLOSE_CURLY},
        {";", TOKEN_SEMI_COLON},
        {",", TOKEN_COMMA},

        {"..<", TOKEN_TO_LESS},
        {"..=", TOKEN_TO_EQUAL},

        {"==", TOKEN_EQUALS},
        {"!=", TOKEN_NOT_EQUALS},
        {">=", TOKEN_GREATER_EQUALS},
        {"<=", TOKEN_LESSER_EQUALS},
        {"<", TOKEN_LEFT_ARROW},
        {">", TOKEN_RIGHT_ARROW},

        {"&&", TOKEN_AND},
        {"||", TOKEN_OR},
        {"!", TOKEN_BANG},
        {"|", TOKEN_PIPE},
        {"~", TOKEN_TILDA},
        {"&", TOKEN_AMPERSAND},
        {"&~", TOKEN_AND_NOT},
        {"<<", TOKEN_SHIFT_LEFT},
        {">>", TOKEN_SHIFT_RIGHT},

        {"+", TOKEN_PLUS},
        {"-", TOKEN_MINUS},
        {"*", TOKEN_STAR},
        {"/", TOKEN_DIVIDE},
        {"%", TOKEN_MOD},
        {"++", TOKEN_PLUS_PLUS},
        {"--", TOKEN_MINUS_MINUS},
        {"**", TOKEN_STAR_STAR},

        {"=>", TOKEN_FAT_ARROW},
        {"->", TOKEN_THIN_ARROW},
        {"|>", TOKEN_PIPE_LINE},
        
        {"@", TOKEN_ABROSE},
        {"#", TOKEN_POUND},
        {"$", TOKEN_DOLLAR},
        {"^", TOKEN_CARROT},
        {".", TOKEN_FULL_STOP},
        {"`", TOKEN_BACK_TICK},
        {"\\", TOKEN_BACK_SLASH},
        {"?", TOKEN_QUESTION},
        
        {"END OF FILE", TOKEN_EOF}
    };

protected:
   TokenKind translate_token_kind_from_string(string token);
public:
    TokenKind kind;
    string word;

    string file_path;
    int row, col;

public:
    Token(string file_path, string word, int row, int col);
    Token();

    void print();
    void check_type();
    void debug();

    Token* END_OF_FILE();

};



/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


