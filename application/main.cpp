#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "error.hpp"
#include "flag.hpp"

inline vector<Flag> flags;

void usage(char **argv) {

    cout << LOGO << endl;
    cout << "Usage: " << argv[0] << " <flags> <path_to_file>" << endl;
    cout << "Flags:" << endl;
    for (int i = 0; i < flags.size(); i++) {
        cout << "    ";
        flags[i].print();
    }
    cout << endl;
}

void debug_tokens(vector<Token> tokens) {
    int total = 0;
    for (int i = 0; i < tokens.size(); ++i) {
        tokens[i].debug();
        cout << endl;
        total++;
    }
    cout << "Total tokens: " << total << endl;
}

void print_tokens(vector<Token> tokens) {
    int total = 0;
    for (int i = 0; i < tokens.size(); ++i) {
        tokens[i].print();
        total++;
    }
    cout << endl;
    cout << "Total tokens: " << total << endl;
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

    flags.push_back(Flag("Debug", {"-d", "-debug"}, "Debug | Developer use only", false));
    flags.push_back(Flag("Print Tokens", {"-p"}, "Print Tokens | Developer use only | To be depricated", false));
    flags.push_back(Flag("Compile", {"-c", "-compile", "-b", "-build"}, "Compiles the project | (Not impliemented yet)", false));
    flags.push_back(Flag("Silent", {"-s", "-silent"}, "Silences the compiler | (Not implemented yet)", false));

    if (argc < 3) {
        usage(argv);
        exit(1);
    }

    path = argv[argc - 1];

    for (int arg_idx = 0; arg_idx < argc; arg_idx++) {
        for (int flag_idx = 0; flag_idx < flags.size(); flag_idx++) {
            if (flags[flag_idx].has(argv[arg_idx])) {
                flags[flag_idx].update();
            }
        }
    }

    vector<Token> tokens = tokenize_with_positions(path);

    for (int i = 0; i < flags.size(); i++) {
        Flag flag = flags[i];
        if (flag.attr == true) {
            if (flag.name == "Debug") {
                debug_tokens(tokens);
            }
            else if (flag.name == "Print Tokens") {
                print_tokens(tokens);
            }
            else if (flag.name == "Compile") {
                cout << "Compile not implimented yet" << endl;
            } 
            else if (flag.name == "Silent") {
                cout << "Silent not implimented yet" << endl;
            }
        } 
    }
}