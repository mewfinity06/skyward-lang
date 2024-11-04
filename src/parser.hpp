#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <vector>
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

const string delims = "!@#$%^&*()_+-={}[]|\\:;\"\'<>,.?/";

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

std::vector<Token> tokenize_with_positions(const std::string &source) {
    std::vector<Token> tokens;
    size_t start = 0;
    int row = 1, col = 1;

    for (size_t end = 0; end < source.size(); ++end) {
        if (delims.find(source[end]) != std::string::npos) {
            // Add the current word as a token if it's not empty
            if (start < end) {
                tokens.push_back(Token(source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            // Add the delimiter as a separate token
            tokens.push_back(Token(std::string(1, source[end]), row, col));
            start = end + 1;
            col++;
        } else if (std::isspace(source[end])) {
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