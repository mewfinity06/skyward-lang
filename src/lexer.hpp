#ifndef LEXER_HPP_
#define LEXER_HPP_

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

string token_kind_to_string(TokenKind kind);

class Token {
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

    Token *END_OF_FILE();

};

std::vector<Token> tokenize_with_positions(const std::string file_path);

const std::string single_char_delims = "!@#$%^&*()_+-={}[]|\\:;\"\'<>,.?/`~";

const std::string comment_start = "//";

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
    "return", "else", "finally", "impl", "const", "mut",
    "defer", "break", "continue", "for", "while",
    "signed", "unsigned", "use", "as"
};

#endif // PARSER_HPP_

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#ifdef LEXER_IMPL_

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

bool is_keyword(const string& str) {
    return keywords.find(str) != keywords.end();
}

bool is_type(const string& str) {
    return types.find(str) != types.end();
}

Token::Token()  
            : kind(TOKEN_UNKNOWN), word(""), col(-1), row(-1) {}

Token::Token(string file_path, string word, int row, int col) 
            : kind(TOKEN_UNKNOWN), word(word), row(row), col(col), file_path(file_path) { check_type(); }

void Token::print()  {
    std::cout << file_path << ":" << row << ":" << col << " |  '" << word << "' \t | " << token_kind_to_string(kind) << std::endl;
}

void Token::debug() {
    std::cout << "[debug] Token {" << std::endl
              << "    Word: " << word << std::endl
              << "    Kind: " << token_kind_to_string(kind) << std::endl
              << "    Row: " << row << " Col: " << col << std::endl;
    std::cout << "}" << std::endl;
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
        else if (is_keyword(word)) {
            kind = TOKEN_KEYWORD;
        }
        else if (is_type(word)) {
            kind = TOKEN_TYPE;
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

string token_kind_to_string(TokenKind kind) {
    switch (kind) {
        case TOKEN_IDENT:               return "TOKEN_IDENT";
        case TOKEN_INT:                 return "TOKEN_INT";
        case TOKEN_KEYWORD:             return "TOKEN_KEYWORD";
        case TOKEN_TYPE:                return "TOKEN_TYPE";
        case TOKEN_STRING:              return "TOKEN_STRING";
        case TOKEN_CHAR:                return "TOKEN_CHAR";
        case TOKEN_PLUS:                return "TOKEN_PLUS";
        case TOKEN_MINUS:               return "TOKEN_MINUS";
        case TOKEN_STAR:                return "TOKEN_STAR";
        case TOKEN_DIVIDE:              return "TOKEN_DIVIDE";
        case TOKEN_MOD:                 return "TOKEN_MOD";
        case TOKEN_ASSIGNMENT:          return "TOKEN_ASSIGNMENT";
        case TOKEN_IMPLICIT_ASSIGNMENT: return "TOKEN_IMPLICIT_ASSIGNMENT";
        case TOKEN_OPEN_PAREN:          return "TOKEN_OPEN_PAREN";
        case TOKEN_CLOSE_PAREN:         return "TOKEN_CLOSE_PAREN";
        case TOKEN_OPEN_BRACKET:        return "TOKEN_OPEN_BRACKET";
        case TOKEN_CLOSE_BRACKET:       return "TOKEN_CLOSE_BRACKET";
        case TOKEN_OPEN_CURLY:          return "TOKEN_OPEN_CURLY";
        case TOKEN_CLOSE_CURLY:         return "TOKEN_CLOSE_CURLY";
        case TOKEN_BANG:                return "TOKEN_BANG";
        case TOKEN_ABROSE:              return "TOKEN_ABROSE";
        case TOKEN_POUND:               return "TOKEN_POUND";
        case TOKEN_CARROT:              return "TOKEN_CARROT";
        case TOKEN_AMPERSAND:           return "TOKEN_AMPERSAND";
        case TOKEN_PIPE:                return "TOKEN_PIPE";
        case TOKEN_LEFT_ARROW:          return "TOKEN_LEFT_ARROW";
        case TOKEN_RIGHT_ARROW:         return "TOKEN_RIGHT_ARROW";
        case TOKEN_COLON:               return "TOKEN_COLON";
        case TOKEN_SEMI_COLON:          return "TOKEN_SEMI_COLON";
        case TOKEN_COMMA:               return "TOKEN_COMMA";
        case TOKEN_FULL_STOP:           return "TOKEN_FULL_STOP";
        case TOKEN_QUESTION:            return "TOKEN_QUESTION";
        case TOKEN_BACK_TICK:           return "TOKEN_BACK_TICK";
        case TOKEN_TILDA:               return "TOKEN_TILDA";
        case TOKEN_BACK_SLASH:          return "TOKEN_BACK_SLASH";          
        case TOKEN_EQUALS:              return "TOKEN_EQUALS";
        case TOKEN_NOT_EQUALS:          return "TOKEN_NOT_EQUALS";
        case TOKEN_GREATER_EQUALS:      return "TOKEN_GREATER_EQUALS";
        case TOKEN_LESSER_EQUALS:       return "TOKEN_LESSER_EQUALS";
        case TOKEN_FAT_ARROW:           return "TOKEN_FAT_ARROW";
        case TOKEN_THIN_ARROW:          return "TOKEN_THIN_ARROW";
        case TOKEN_PIPE_LINE:           return "TOKEN_PIPE_LINE";
        case TOKEN_PLUS_PLUS:           return "TOKEN_PLUS_PLUS";
        case TOKEN_MINUS_MINUS:         return "TOKEN_MINUS_MINUS";
        case TOKEN_STAR_STAR:           return "TOKEN_STAR_STAR";
        case TOKEN_AND:                 return "TOKEN_AND";
        case TOKEN_OR:                  return "TOKEN_OR";
        case TOKEN_EOF:                 return "TOKEN_EOF";
        case TOKEN_UNKNOWN:             return "TOKEN_UNKNOWN";
        default:                        return "UNKNOWN_TOKEN_KIND";
    }
}


std::vector<Token> tokenize_with_positions(const std::string file_path) {
    std::vector<Token> tokens;
    size_t start = 0;
    int row = 1, col = 1;

    std::ifstream t(file_path);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    char* buffer = (char*) malloc(size);
    t.seekg(0);
    t.read(&buffer[0], size);

    string source = buffer;

    for (size_t end = 0; end < source.size(); ++end) {
        // Check for single-line comments
        if (source.substr(end, 2) == comment_start) {
            // Add the preceding token if any
            if (start < end) {
                tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
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
                    tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
                }
                // Add the two-character token
                tokens.push_back(Token(file_path, two_char_token, row, col));
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

            tokens.push_back(Token(file_path, source.substr(literal_start, end - literal_start), row, col - static_cast<int>(end - literal_start)));
            start = end;
            continue;
        }

        // Single-character delimiter handling
        if (single_char_delims.find(source[end]) != std::string::npos) {
            if (start < end) {
                tokens.push_back(Token(file_path,  source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            tokens.push_back(Token(file_path, std::string(1, source[end]), row, col));
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
                tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            start = end + 1;
        } else {
            col++;
        }
    }

    // Add the last token if any
    if (start < source.size()) {
        tokens.push_back(Token(file_path, source.substr(start), row, col - static_cast<int>(source.size() - start)));
    }

    tokens.push_back(Token(file_path, "END OF FILE", -1, -1));

    return tokens;
}

#endif // PARSER_IMPL_ 