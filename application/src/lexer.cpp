#include "lexer.hpp"
#include "magic_enum/magic_enum.hpp"

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

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

    std::ifstream t(file_path);

    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    t.seekg(0);
    char* buffer = (char*)malloc(size + 1);

    if (!buffer) {
        err = Error(Error::ErrorKind::ErrorMemory, "Could not allocate memory for buffer");
        err.print();
        return tokens;
    }

    t.read(buffer, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    std::string source(buffer);
    free(buffer);

    while (start < source.size()) {
        size_t max_token_length = 3; // Maximum length of a multi-character token
        size_t end = start;

        // Step 1: Handle comments
        if (source.substr(end, 2) == comment_start) {
            if (start < end) {
                tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            while (end < source.size() && source[end] != '\n') {
                end++;
            }
            start = end + 1;
            row++;
            col = 1;
            continue;
        }

        // Step 2: Check for multi-character tokens
        std::string found_token;
        for (int len = max_token_length; len > 0; len--) {
            if (end + len <= source.size()) {
                std::string potential_token = source.substr(end, len);
                if (non_word_tokens.find(potential_token) != non_word_tokens.end()) {
                    found_token = potential_token;
                    break;
                }
            }
        }

        // If we found a multi-character token
        if (!found_token.empty()) {
            if (start < end) {
                tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            tokens.push_back(Token(file_path, found_token, row, col));
            start = end + found_token.size();
            col += found_token.size();
            continue;
        }

        // Step 3: Handle single-character tokens or delimiters
        std::string single_char = source.substr(end, 1);
        if (non_word_tokens.find(single_char) != non_word_tokens.end()) {
            if (start < end) {
                tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            }
            tokens.push_back(Token(file_path, single_char, row, col));
            start = end + 1;
            col++;
            continue;
        }

        // Step 4: Handle identifiers (alphanumeric words)
        if (std::isalnum(source[end]) || source[end] == '_') {
            while (end < source.size() && (std::isalnum(source[end]) || source[end] == '_')) {
                end++;
                col++;
            }
            tokens.push_back(Token(file_path, source.substr(start, end - start), row, col - static_cast<int>(end - start)));
            start = end;
            continue;
        }

        // Step 5: Handle whitespace
        if (std::isspace(source[end])) {
            if (source[end] == '\n') {
                row++;
                col = 1;
            } else {
                col++;
            }
            start = end + 1;
        } else {
            col++;
            end++;
            start = end;
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

inline Token::Token(string file_path, string word, int row, int col) :
    kind(TokenKind::TOKEN_UNKNOWN), word(word),
    row(row), col(col), file_path(file_path)
{
    check_type();
}

Token::Token() : kind(TokenKind::TOKEN_UNKNOWN), word(""), col(-1), row(-1) {}

void Token::print() {
    // std::cout << file_path << ":" << row << ":" << col << " |  '" << word << "' \t | " << token_kind_to_string(kind) << std::endl;
    std::cout << word << ", ";
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
