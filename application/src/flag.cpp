#include "flag.hpp"

Flag::Flag(const vector<string>& flags, const string desc, bool var) : flags(flags), desc(desc), var(var) {}

Flag::Flag() : flags({"hello", "world"}), desc("test"), var(true) {}

bool Flag::has(string word) {
    for (int i = 0; i < flags.size(); i++) {
        if (word == flags[i]) { return true; }
    }
    return false;
}

int Flag::size() {
    return flags.size();
}

void Flag::print() {
    for (int i = 0; i < flags.size(); i++) {
        std::cout << flags[i] << " ";
    }
    std::cout << "| " << desc << " | Default ";
    if (var) {
        std::cout << "true";
    } else {
        std::cout << "false";
    }
    std::cout << std::endl;
}

void Flag::update() {
    var = !var;
}
