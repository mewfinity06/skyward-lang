#pragma once
#include "common.hpp"
#include "error.hpp"
#include <cctype>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <variant>

// Forward declarations
class Token;

const std::string single_char_delims = "!@#$%^&*()_+-={}[]|\\:;\"\'<>,.?/`~";

const std::string comment_start = "//";

const std::unordered_set<std::string> non_word_tokens = {
    // Assignment
    ":", "=", ":=", "+=", "-=", "*=", "/=", "%=", "|=", "~=",
    "&=", "&~=", "<<=", ">==", "&&=", "||=",
    // Seperators
    "{", "}", "(", ")", "[", "]", ";", ",", 
    // Iterators
    "..<", "..=", 
    // Comparison
    "==", "!=", "<=", ">=",
    // Logical operators
    "&&", "||", "!", "|", "~", "&", "&~", "<<", ">>", 
    // Arithmetic
    "+", "-", "*", "%", "++", "--", "**",
    // Misc
    "<", ">", "@", "#", "$", "^"
};

const std::unordered_set<std::string> multi_char_tokens = {
    "<=", ">=", "==", "!=", "&&", "||", "++", "--", "**",
    "->", "=>", "||", "&&", "|>", ":=",
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

    TOKEN_KEYWORD,
    TOKEN_TYPE,

    TOKEN_STRING,
    TOKEN_CHAR,

    // Binary Tokens
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_DIVIDE,
    TOKEN_MOD,

    TOKEN_ASSIGNMENT,          // =
    TOKEN_IMPLICIT_ASSIGNMENT, // :=

    // Seperator tokens
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_OPEN_CURLY,
    TOKEN_CLOSE_CURLY,

    // Single char tokens
    TOKEN_BANG,        // !
    TOKEN_ABROSE,      // @
    TOKEN_POUND,       // #
    TOKEN_CARROT,      // ^
    TOKEN_AMPERSAND,   // &
    TOKEN_PIPE,        // |
    TOKEN_LEFT_ARROW,  // <
    TOKEN_RIGHT_ARROW, // >
    TOKEN_COLON,       // :
    TOKEN_SEMI_COLON,  // ;
    TOKEN_COMMA,       // ,
    TOKEN_FULL_STOP,   // .
    TOKEN_QUESTION,    // ?
    TOKEN_BACK_TICK,   // `
    TOKEN_TILDA,       // ~
    TOKEN_BACK_SLASH,

    // Multichar non alphanumeric tokens
    TOKEN_EQUALS,         // ==
    TOKEN_NOT_EQUALS,     // !=
    TOKEN_GREATER_EQUALS, // >=
    TOKEN_LESSER_EQUALS,  // <=

    TOKEN_FAT_ARROW,  // =>
    TOKEN_THIN_ARROW, // ->
    TOKEN_PIPE_LINE,  // |> (Thanks Gleam!)

    TOKEN_PLUS_PLUS,   // ++
    TOKEN_MINUS_MINUS, // --
    TOKEN_STAR_STAR,   // **

    TOKEN_AND, // &&
    TOKEN_OR,  // ||

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
        {"*", TOKEN_STAR},
        {"/", TOKEN_DIVIDE},
        {"+", TOKEN_PLUS},
        {"-", TOKEN_MINUS},
        {"%", TOKEN_MOD},
        {"=", TOKEN_ASSIGNMENT},
        {":=", TOKEN_IMPLICIT_ASSIGNMENT},
        {"(", TOKEN_OPEN_PAREN},
        {")", TOKEN_CLOSE_PAREN},
        {"[", TOKEN_OPEN_BRACKET},
        {"]", TOKEN_CLOSE_BRACKET},
        {"{", TOKEN_OPEN_CURLY},
        {"}", TOKEN_CLOSE_CURLY},
        {"!", TOKEN_BANG},
        {"@", TOKEN_ABROSE},
        {"#", TOKEN_POUND},
        {"^", TOKEN_CARROT},
        {"&", TOKEN_AMPERSAND},
        {"|", TOKEN_PIPE},
        {"<", TOKEN_LEFT_ARROW},
        {">", TOKEN_RIGHT_ARROW},
        {":", TOKEN_COLON},
        {";", TOKEN_SEMI_COLON},
        {",", TOKEN_COMMA},
        {".", TOKEN_FULL_STOP},
        {"?", TOKEN_QUESTION},
        {"`", TOKEN_BACK_TICK},
        {"~", TOKEN_TILDA},
        {"\\", TOKEN_BACK_SLASH},
        {"==", TOKEN_EQUALS},
        {"!=", TOKEN_NOT_EQUALS},
        {">=", TOKEN_GREATER_EQUALS},
        {"<=", TOKEN_LESSER_EQUALS},
        {"=>", TOKEN_FAT_ARROW},
        {"->", TOKEN_THIN_ARROW},
        {"|>", TOKEN_PIPE_LINE},
        {"++", TOKEN_PLUS_PLUS},
        {"--", TOKEN_MINUS_MINUS},
        {"**", TOKEN_STAR_STAR},
        {"&&", TOKEN_AND},
        {"||", TOKEN_OR},
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
    Token(string word, string file_path, int row, int col);
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


