#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "error.hpp"



void usage(char **argv) {
    std::cout << "Usage: " << argv[0] << " <flags> <path_to_file>" << std::endl;
    std::cout << "Flags:" << std::endl;
    std::cout << "    -d, -debug    Debug" << std::endl;
}

void print_tokens(vector<Token> tokens) {
    int total = 0;
    for (int i = 0; i < tokens.size(); ++i) {
        tokens[i].print();
        total++;
    }
    std::cout << "Total tokens: " << total << std::endl;
}

void debug_tokens(std::vector<Token> tokens) {
    int total = 0;
    for (int i = 0; i < tokens.size(); ++i) {
        tokens[i].debug();
        std::cout << std::endl;
        total++;
    }
    std::cout << "Total tokens: " << total << std::endl;
}

string get_file_contents(string file_path) {
    std::ifstream t(file_path);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    char* buffer = (char*) malloc(size);
    t.seekg(0);
    t.read(&buffer[0], size);
    return buffer; 
}

int main(int argc, char **argv) {

    string path;
    std::vector<string> flags;

    if (argc < 2) {
        usage(argv);
        exit(1);
    }

    path = argv[argc - 1];

    for (int i = 1; i < argc - 1; ++i) {
        flags.push_back(argv[i]);
    }

    for (int i = 0; i < flags.size(); ++i) {
        if (flags.at(i) == "-d" || flags.at(i) == "-debug") {
            DEBUG = true;
        }
    }

    std::vector<Token> words = tokenize_with_positions(path);

}