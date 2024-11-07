#include "flag.hpp"

Flag::Flag(const vector<string>& flags, const string desc, void* attr) : flags(flags), desc(desc), attr(attr) {}

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

void Flag::update(void* new_attr) {
    attr = new_attr;
}
