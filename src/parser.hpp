#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <sstream>


typedef std::string string;

enum TokenKind {
    // Multichar tokens
    TOKEN_IDENT,
    TOKEN_INT,

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

class Token {
public:
    TokenKind kind;
    string word;
    int row, col;

public:
    Token(string word, int row, int col);
    Token();

    void print();
    void check_type();

    Token *END_OF_FILE();

};

std::vector<Token> tokenize_with_positions(const std::string &source);
void print_word(Token word);

#endif // PARSER_HPP_

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#ifdef PARSER_IMPL_

bool can_convert_to_int(const string& str) {
    std::stringstream ss(str);
    int num;
    char ch;
    return (ss >> num) && !(ss >> ch); 
}

bool is_identifier(const string& str) {
    if (isalpha(str[0]) || str[0] == *"_") {
        return true;
    }
    return false;
}

Token::Token()  
            : kind(TOKEN_UNKNOWN), word(""), col(-1), row(-1) {}

Token::Token(string word, int row, int col) 
            : kind(TOKEN_UNKNOWN), word(word), row(row), col(col) { check_type(); }

void Token::print()  {
    std::cout << "Token { " << std::endl <<
                 "    Kind: " << kind << std::endl <<
                 "    Token: \"" << word << "\"" << std::endl << 
                 "    Row: " << row << " " << " Col: " << col << std::endl <<
                 "}" << std::endl;
}

Token *Token::END_OF_FILE() {
    Token *eof = new Token();
    eof->word = "END OF FILE";
    eof->kind = TOKEN_EOF;
    eof->row = -1;
    eof->col = -1;
    return eof;
}

void Token::check_type() {
    if (can_convert_to_int(word)) {
        kind = TOKEN_INT;
    } else {
        if (word == "*") {
            kind = TOKEN_STAR;
        } 
        else if (word == "/") {
            kind = TOKEN_DIVIDE;
        } 
        else if (word == "+") {
            kind = TOKEN_PLUS;
        } 
        else if (word == "-") {
            kind = TOKEN_MINUS;
        }
        else if (word == "%") {
            kind = TOKEN_MOD;
        }
        else if (word == "=") {
            kind = TOKEN_ASSIGNMENT;
        }
        else if (word == ":=") {
            kind = TOKEN_IMPLICIT_ASSIGNMENT;
        }
        else if (word == "(") {
            kind = TOKEN_OPEN_PAREN;
        }
        else if (word == ")") {
            kind = TOKEN_CLOSE_PAREN;
        }
        else if (word == "[") {
            kind = TOKEN_OPEN_BRACKET;
        }
        else if (word == "]") {
            kind = TOKEN_CLOSE_BRACKET;
        }
        else if (word == "{") {
            kind = TOKEN_OPEN_CURLY;
        }
        else if (word == "}") {
            kind = TOKEN_CLOSE_CURLY;
        }
        else if (word == "!") {
            kind = TOKEN_BANG;
        }
        else if (word == "@") {
            kind = TOKEN_ABROSE;
        }
        else if (word == "#") {
            kind = TOKEN_POUND;
        }
        else if (word == "^") {
            kind = TOKEN_CARROT;
        }
        else if (word == "&") {
            kind = TOKEN_AMPERSAND;
        }
        else if (word == "|") {
            kind = TOKEN_PIPE;
        }
        else if (word == "<") {
            kind = TOKEN_LEFT_ARROW;
        }
        else if (word == ">") {
            kind = TOKEN_RIGHT_ARROW;
        }
        else if (word == ":") {
            kind = TOKEN_COLON;
        }
        else if (word == ";") {
            kind = TOKEN_SEMI_COLON;
        }
        else if (word == ",") {
            kind = TOKEN_COMMA;
        }
        else if (word == ".") {
            kind = TOKEN_FULL_STOP;
        }
        else if (word == "?") {
            kind = TOKEN_QUESTION;
        }
        else if (word == "`") {
            kind = TOKEN_BACK_TICK;
        }
        else if (word == "~") {
            kind = TOKEN_TILDA;
        }
        else if (word == "\\") {
            kind = TOKEN_BACK_SLASH;
        }
        else if (word == "==") {
            kind = TOKEN_EQUALS;
        }
        else if (word == "!=") {
            kind = TOKEN_NOT_EQUALS;
        }
        else if (word == ">=") {
            kind = TOKEN_GREATER_EQUALS;
        }
        else if (word == "<=") {
            kind = TOKEN_LESSER_EQUALS;
        }
        else if (word == "=>") {
            kind = TOKEN_FAT_ARROW;
        }
        else if (word == "->") {
            kind = TOKEN_THIN_ARROW;
        }
        else if (word == "|>") {
            kind = TOKEN_PIPE_LINE;
        }
        else if (word == "++") {
            kind = TOKEN_PLUS_PLUS;
        }
        else if (word == "--") {
            kind = TOKEN_MINUS_MINUS;
        }
        else if (word == "**") {
            kind = TOKEN_STAR_STAR;
        }
        else if (word == "&&") {
            kind = TOKEN_AND;
        }
        else if (word == "||") {
            kind = TOKEN_OR;
        }
        else if (is_identifier(word)) {
            kind = TOKEN_IDENT;
        }
        else if (word[0] == *"\"" && word.back() == *"\"") {
            kind = TOKEN_STRING;
        }
        else if (word[0] == *"'" && word.back() == *"'") {
            kind = TOKEN_CHAR;
        }
        else if (word == "END OF FILE") {
            kind = TOKEN_EOF;
        }
        else {
            kind = TOKEN_UNKNOWN;
        }
    }
}

const std::string single_char_delims = "!@#$%^&*()_+-={}[]|\\:;\"\'<>,.?/`~";
const std::unordered_set<std::string> multi_char_tokens = {
    "<=", ">=", "==", "!=", "&&", "||", "++", "--",
    "->", "=>", "||", "&&", "|>"
};
const std::string comment_start = "//";

std::vector<Token> tokenize_with_positions(const std::string &source) {
    std::vector<Token> tokens;
    size_t start = 0;
    int row = 1, col = 1;

    for (size_t end = 0; end < source.size(); ++end) {
        // Check for single-line comments
        if (source.substr(end, 2) == comment_start) {
            // Add the preceding token if any
            if (start < end) {
                tokens.push_back(Token(source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            // Move end to the end of the line
            while (end < source.size() && source[end] != '\n') {
                end++;
            }
            start = end + 1;
            row++;
            col = 1;
            continue;
        }

        // Check for multi-character tokens (like <=, >=) by looking at two characters at a time
        if (end < source.size() - 1) {
            std::string two_char_token = source.substr(end, 2);
            if (multi_char_tokens.find(two_char_token) != multi_char_tokens.end()) {
                // Add the preceding word token if any
                if (start < end) {
                    tokens.push_back(Token(source.substr(start, end - start), row, col - static_cast<int>(end - start)));
                }
                // Add the two-character token
                tokens.push_back(Token(two_char_token, row, col));
                start = end + 2;
                col += 2;
                end++;
                continue;
            }
        }

        // Check for strings and character literals
        if (source[end] == '"' || source[end] == '\'') {
            char quote_type = source[end];
            size_t literal_start = end;
            end++;
            col++;

            // Capture the entire string or character literal
            while (end < source.size() && source[end] != quote_type) {
                if (source[end] == '\\' && end + 1 < source.size()) {
                    end += 2;  // Skip over escape sequences
                    col += 2;
                } else {
                    end++;
                    col++;
                }
            }

            // Include the closing quote in the token
            if (end < source.size()) {
                end++;
                col++;
            }

            tokens.push_back(Token(source.substr(literal_start, end - literal_start), row, col - static_cast<int>(end - literal_start)));
            start = end;
            continue;
        }

        // Single-character delimiter handling
        if (single_char_delims.find(source[end]) != std::string::npos) {
            if (start < end) {
                tokens.push_back(Token(source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            tokens.push_back(Token(std::string(1, source[end]), row, col));
            start = end + 1;
            col++;
        } else if (std::isspace(source[end])) {
            // Handle whitespace and update row and column tracking
            if (source[end] == '\n') {
                row++;
                col = 1;
            } else {
                col++;
            }
            if (start < end) {
                tokens.push_back(Token(source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            start = end + 1;
        } else {
            col++;
        }
    }

    // Add the last token if any
    if (start < source.size()) {
        tokens.push_back(Token(source.substr(start), row, col - static_cast<int>(source.size() - start)));
    }

    tokens.push_back(Token("END OF FILE", -1, -1));

    return tokens;
}

void print_word(Token word) {
    std::cout << "Token: \"" << word.word << "\"" << std::endl
              << "    row: " << word.row << std::endl
              << "    col: " << word.col << std::endl;
}

#endif // PARSER_IMPL_ 