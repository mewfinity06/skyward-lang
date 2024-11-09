#include "flag.hpp"

Flag::Flag(const string name, const vector<string>& flags, 
           const string desc, bool attr) 
: name(name), flags(flags), desc(desc), attr(attr) {}

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
    std::cout << "| " << desc << std::endl;
}

void Flag::update() {
    attr = !attr;
}
