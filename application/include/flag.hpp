#pragma once
#include "common.hpp"
#include "error.hpp"

class Flag {
public:
    vector<string> flags;
    string desc;
    bool var;

public:
    Flag(const vector<string>& flags, const string desc, bool var);
    Flag();

    bool has(string word);
    int size();

    void print();

    void update();
};