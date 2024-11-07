#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "error.hpp"
#include "flag.hpp"

inline vector<Flag> flags;

void usage(char **argv) {

    std::cout
    << "------------------------------" << std::endl
    << "            ()                " << std::endl
    << "            )(                " << std::endl
    << "         o======o             " << std::endl
    << "            ||                " << std::endl 
    << "            ||                " << std::endl
    << "            ||                " << std::endl
    << "       ,c88888888b            " << std::endl
    << "      ,88888888888b           " << std::endl
    << "      88888888888Y\"          " << std::endl
    << ",,;,,;;\"Y888888Y\",,,,,,,;;,;" << std::endl
    << "------------------------------" << std::endl
    << "       S K Y W A R D          " << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: " << argv[0] << " <flags> <path_to_file>" << std::endl;
    std::cout << "Flags:" << std::endl;
    for (int i = 0; i < flags.size(); i++) {
        std::cout << "    ";
        flags[i].print();
    }
    std::cout << std::endl;
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

void debug_flags() {
    for (int i = 0; i < flags.size(); i++) {
        flags[i].print();
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

    string path;

    flags.push_back(Flag({"-c", "-compile", "-build"}, "Compiles the project | (Not impliemented yet)", (void*)false));
    flags.push_back(Flag({"-d", "-debug"}, "DEBUG", (void*)false));
    flags.push_back(Flag({"-s", "-silent"}, "Silences the compiler | (Not implemented yet)", (void*)false));

    if (argc < 2) {
        usage(argv);
        exit(1);
    }

    path = argv[argc - 1];

    for (int arg_idx = 0; arg_idx < argc; arg_idx++) {
        for (int flag_idx = 0; flag_idx < flags.size(); flag_idx++) {
            if (flags[flag_idx].has(argv[arg_idx])) {
                // std::cout << "Found: " << argv[arg_idx] << std::endl;
                flags[flag_idx].update((void*)1);
            }
        }
    }

    // vector<Token> words = tokenize_with_positions(path);
    // debug_tokens(words);
}