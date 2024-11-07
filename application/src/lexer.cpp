#include "lexer.hpp"
#include "magic_enum/magic_enum.hpp"

string token_kind_to_string(TokenKind kind) {
    // static casting because magic_enum::enum_name() returns a string_view
    return static_cast<string>(magic_enum::enum_name(kind)); 
}

TokenKind Token::translate_token_kind_from_string(string token) {
    TokenKind token_kind;
    try {
        token_kind = Token::string_token_to_enum_dictionary.at(token);
    }
    catch (std::exception& exception) {
        if (is_keyword(token)) {
            token_kind = TokenKind::TOKEN_KEYWORD;
        }
        else if (is_type(token)) {
            token_kind = TokenKind::TOKEN_TYPE;
        }
        else if (is_identifier(token)) {
            token_kind = TokenKind::TOKEN_IDENT;
        }
        else if (word[0] == *"\"" && word.back() == *"\"") {
            token_kind = TokenKind::TOKEN_STRING;
        }
        else if (word[0] == *"'" && word.back() == *"'") {
            token_kind = TokenKind::TOKEN_CHAR;
        }
        else {
            token_kind = TokenKind::TOKEN_UNKNOWN;
        }
    }

    return token_kind;
}

std::vector<Token> tokenize_with_positions(const std::string file_path) {

    std::vector<Token> tokens;
    size_t start = 0;
    int row = 1, col = 1;

    Error err = Error();

    std::ifstream t = std::ifstream(file_path);

    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    char* buffer = (char*)malloc(size);

    if (!buffer) {
        err = Error(Error::ErrorKind::ErrorMemory, "Could not allocate memory for buffer");
        err.print();
        return tokens;
    }

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
                }
                else {
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
                tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            tokens.push_back(Token(file_path, std::string(1, source[end]), row, col));
            start = end + 1;
            col++;
        }
        else if (std::isspace(source[end])) {
            // Handle whitespace and update row and column tracking
            if (source[end] == '\n') {
                row++;
                col = 1;
            }
            else {
                col++;
            }
            if (start < end) {
                tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            start = end + 1;
        }
        else {
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

inline Token::Token(string word, string file_path, int row, int col) :
    kind(TokenKind::TOKEN_UNKNOWN), word(word),
    row(row), col(col), file_path(file_path)
{
    check_type();
}

Token::Token() : kind(TokenKind::TOKEN_UNKNOWN), word(""), col(-1), row(-1) {}

void Token::print() {
    std::cout << file_path << ":" << row << ":" << col << " |  '" << word << "' \t | " << token_kind_to_string(kind) << std::endl;
}

void Token::check_type() {
    if (can_convert_to_int(word)) {
        kind = TokenKind::TOKEN_INT;
    }
    else {
        this->kind = translate_token_kind_from_string(word);
    }
}

void Token::debug() {
    std::cout << "[debug] Token {" << std::endl
        << "    Word: " << word << std::endl
        << "    Kind: " << token_kind_to_string(kind) << std::endl
        << "    Row: " << row << " Col: " << col << std::endl;
    std::cout << "}" << std::endl;
}

Token* Token::END_OF_FILE() {
    Token* eof = new Token();
    eof->word = "END OF FILE";
    eof->kind = TokenKind::TOKEN_EOF;
    eof->row = -1;
    eof->col = -1;
    return eof;
}
