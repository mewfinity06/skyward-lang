#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <sstream>


#include "typedefs.hpp"


enum TokenKind {
    TOKEN_IDENT,
    TOKEN_NUMBER,
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

bool canConvertToInt(const std::string& str) {
    std::stringstream ss(str);
    int num;
    char ch;
    return (ss >> num) && !(ss >> ch); 
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

void Token::check_type() {
    if (canConvertToInt(word)) {
        kind = TOKEN_NUMBER;
    } else {
        kind = TOKEN_IDENT;
    }
}

const std::string single_char_delims = "!@#$%^&*()_+-={}[]|\\:;\"\'<>,.?/";
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

    return tokens;
}

void print_word(Token word) {
    std::cout << "Token: \"" << word.word << "\"" << std::endl
              << "    row: " << word.row << std::endl
              << "    col: " << word.col << std::endl;
}

#endif // PARSER_IMPL_ 