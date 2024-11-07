#include "lexer.hpp"

string token_kind_to_string(TokenKind kind) {

    switch (kind) {
        case TokenKind::TOKEN_IDENT:               return "TOKEN_IDENT";
        case TokenKind::TOKEN_INT:                 return "TOKEN_INT";
        case TokenKind::TOKEN_KEYWORD:             return "TOKEN_KEYWORD";
        case TokenKind::TOKEN_TYPE:                return "TOKEN_TYPE";
        case TokenKind::TOKEN_STRING:              return "TOKEN_STRING";
        case TokenKind::TOKEN_CHAR:                return "TOKEN_CHAR";
        case TokenKind::TOKEN_PLUS:                return "TOKEN_PLUS";
        case TokenKind::TOKEN_MINUS:               return "TOKEN_MINUS";
        case TokenKind::TOKEN_STAR:                return "TOKEN_STAR";
        case TokenKind::TOKEN_DIVIDE:              return "TOKEN_DIVIDE";
        case TokenKind::TOKEN_MOD:                 return "TOKEN_MOD";
        case TokenKind::TOKEN_ASSIGNMENT:          return "TOKEN_ASSIGNMENT";
        case TokenKind::TOKEN_IMPLICIT_ASSIGNMENT: return "TOKEN_IMPLICIT_ASSIGNMENT";
        case TokenKind::TOKEN_OPEN_PAREN:          return "TOKEN_OPEN_PAREN";
        case TokenKind::TOKEN_CLOSE_PAREN:         return "TOKEN_CLOSE_PAREN";
        case TokenKind::TOKEN_OPEN_BRACKET:        return "TOKEN_OPEN_BRACKET";
        case TokenKind::TOKEN_CLOSE_BRACKET:       return "TOKEN_CLOSE_BRACKET";
        case TokenKind::TOKEN_OPEN_CURLY:          return "TOKEN_OPEN_CURLY";
        case TokenKind::TOKEN_CLOSE_CURLY:         return "TOKEN_CLOSE_CURLY";
        case TokenKind::TOKEN_BANG:                return "TOKEN_BANG";
        case TokenKind::TOKEN_ABROSE:              return "TOKEN_ABROSE";
        case TokenKind::TOKEN_POUND:               return "TOKEN_POUND";
        case TokenKind::TOKEN_CARROT:              return "TOKEN_CARROT";
        case TokenKind::TOKEN_AMPERSAND:           return "TOKEN_AMPERSAND";
        case TokenKind::TOKEN_PIPE:                return "TOKEN_PIPE";
        case TokenKind::TOKEN_LEFT_ARROW:          return "TOKEN_LEFT_ARROW";
        case TokenKind::TOKEN_RIGHT_ARROW:         return "TOKEN_RIGHT_ARROW";
        case TokenKind::TOKEN_COLON:               return "TOKEN_COLON";
        case TokenKind::TOKEN_SEMI_COLON:          return "TOKEN_SEMI_COLON";
        case TokenKind::TOKEN_COMMA:               return "TOKEN_COMMA";
        case TokenKind::TOKEN_FULL_STOP:           return "TOKEN_FULL_STOP";
        case TokenKind::TOKEN_QUESTION:            return "TOKEN_QUESTION";
        case TokenKind::TOKEN_BACK_TICK:           return "TOKEN_BACK_TICK";
        case TokenKind::TOKEN_TILDA:               return "TOKEN_TILDA";
        case TokenKind::TOKEN_BACK_SLASH:          return "TOKEN_BACK_SLASH";
        case TokenKind::TOKEN_EQUALS:              return "TOKEN_EQUALS";
        case TokenKind::TOKEN_NOT_EQUALS:          return "TOKEN_NOT_EQUALS";
        case TokenKind::TOKEN_GREATER_EQUALS:      return "TOKEN_GREATER_EQUALS";
        case TokenKind::TOKEN_LESSER_EQUALS:       return "TOKEN_LESSER_EQUALS";
        case TokenKind::TOKEN_FAT_ARROW:           return "TOKEN_FAT_ARROW";
        case TokenKind::TOKEN_THIN_ARROW:          return "TOKEN_THIN_ARROW";
        case TokenKind::TOKEN_PIPE_LINE:           return "TOKEN_PIPE_LINE";
        case TokenKind::TOKEN_PLUS_PLUS:           return "TOKEN_PLUS_PLUS";
        case TokenKind::TOKEN_MINUS_MINUS:         return "TOKEN_MINUS_MINUS";
        case TokenKind::TOKEN_STAR_STAR:           return "TOKEN_STAR_STAR";
        case TokenKind::TOKEN_AND:                 return "TOKEN_AND";
        case TokenKind::TOKEN_OR:                  return "TOKEN_OR";
        case TokenKind::TOKEN_EOF:                 return "TOKEN_EOF";
        case TokenKind::TOKEN_UNKNOWN:             return "TOKEN_UNKNOWN";
        default:                        return "UNKNOWN_TOKEN_KIND";
    }
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
        err = Error(Error::ErrorMemory, "Could not allocate memory for buffer");
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
        if (word == "*") {
            kind = TokenKind::TOKEN_STAR;
        }
        else if (word == "/") {
            kind = TokenKind::TOKEN_DIVIDE;
        }
        else if (word == "+") {
            kind = TokenKind::TOKEN_PLUS;
        }
        else if (word == "-") {
            kind = TokenKind::TOKEN_MINUS;
        }
        else if (word == "%") {
            kind = TokenKind::TOKEN_MOD;
        }
        else if (word == "=") {
            kind = TokenKind::TOKEN_ASSIGNMENT;
        }
        else if (word == ":=") {
            kind = TokenKind::TOKEN_IMPLICIT_ASSIGNMENT;
        }
        else if (word == "(") {
            kind = TokenKind::TOKEN_OPEN_PAREN;
        }
        else if (word == ")") {
            kind = TokenKind::TOKEN_CLOSE_PAREN;
        }
        else if (word == "[") {
            kind = TokenKind::TOKEN_OPEN_BRACKET;
        }
        else if (word == "]") {
            kind = TokenKind::TOKEN_CLOSE_BRACKET;
        }
        else if (word == "{") {
            kind = TokenKind::TOKEN_OPEN_CURLY;
        }
        else if (word == "}") {
            kind = TokenKind::TOKEN_CLOSE_CURLY;
        }
        else if (word == "!") {
            kind = TokenKind::TOKEN_BANG;
        }
        else if (word == "@") {
            kind = TokenKind::TOKEN_ABROSE;
        }
        else if (word == "#") {
            kind = TokenKind::TOKEN_POUND;
        }
        else if (word == "^") {
            kind = TokenKind::TOKEN_CARROT;
        }
        else if (word == "&") {
            kind = TokenKind::TOKEN_AMPERSAND;
        }
        else if (word == "|") {
            kind = TokenKind::TOKEN_PIPE;
        }
        else if (word == "<") {
            kind = TokenKind::TOKEN_LEFT_ARROW;
        }
        else if (word == ">") {
            kind = TokenKind::TOKEN_RIGHT_ARROW;
        }
        else if (word == ":") {
            kind = TokenKind::TOKEN_COLON;
        }
        else if (word == ";") {
            kind = TokenKind::TOKEN_SEMI_COLON;
        }
        else if (word == ",") {
            kind = TokenKind::TOKEN_COMMA;
        }
        else if (word == ".") {
            kind = TokenKind::TOKEN_FULL_STOP;
        }
        else if (word == "?") {
            kind = TokenKind::TOKEN_QUESTION;
        }
        else if (word == "`") {
            kind = TokenKind::TOKEN_BACK_TICK;
        }
        else if (word == "~") {
            kind = TokenKind::TOKEN_TILDA;
        }
        else if (word == "\\") {
            kind = TokenKind::TOKEN_BACK_SLASH;
        }
        else if (word == "==") {
            kind = TokenKind::TOKEN_EQUALS;
        }
        else if (word == "!=") {
            kind = TokenKind::TOKEN_NOT_EQUALS;
        }
        else if (word == ">=") {
            kind = TokenKind::TOKEN_GREATER_EQUALS;
        }
        else if (word == "<=") {
            kind = TokenKind::TOKEN_LESSER_EQUALS;
        }
        else if (word == "=>") {
            kind = TokenKind::TOKEN_FAT_ARROW;
        }
        else if (word == "->") {
            kind = TokenKind::TOKEN_THIN_ARROW;
        }
        else if (word == "|>") {
            kind = TokenKind::TOKEN_PIPE_LINE;
        }
        else if (word == "++") {
            kind = TokenKind::TOKEN_PLUS_PLUS;
        }
        else if (word == "--") {
            kind = TokenKind::TOKEN_MINUS_MINUS;
        }
        else if (word == "**") {
            kind = TokenKind::TOKEN_STAR_STAR;
        }
        else if (word == "&&") {
            kind = TokenKind::TOKEN_AND;
        }
        else if (word == "||") {
            kind = TokenKind::TOKEN_OR;
        }
        else if (is_keyword(word)) {
            kind = TokenKind::TOKEN_KEYWORD;
        }
        else if (is_type(word)) {
            kind = TokenKind::TOKEN_TYPE;
        }
        else if (is_identifier(word)) {
            kind = TokenKind::TOKEN_IDENT;
        }
        else if (word[0] == *"\"" && word.back() == *"\"") {
            kind = TokenKind::TOKEN_STRING;
        }
        else if (word[0] == *"'" && word.back() == *"'") {
            kind = TokenKind::TOKEN_CHAR;
        }
        else if (word == "END OF FILE") {
            kind = TokenKind::TOKEN_EOF;
        }
        else {
            kind = TokenKind::TOKEN_UNKNOWN;
        }
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
