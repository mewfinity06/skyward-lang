#include <iostream>
#include <fstream>
#include <vector>

#include "src/typedefs.hpp"

#define PARSER_IMPL_
#include "src/parser.hpp"

void usage(char **argv) {
    std::cout << "Usage: " << argv[0] << " <path_to_file>" << std::endl;
}

void print_all(std::vector<Token> tokens) {
    for (int i = 0; i < tokens.size(); ++i) {
        std::cout << i << " ";
        tokens[i].print();
        std::cout << std::endl;
    }
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

    if (argc < 2) {
        usage(argv);
        exit(1);
    }

    string contents = get_file_contents(argv[1]);

    std::vector<Token> words = tokenize_with_positions(contents);

}