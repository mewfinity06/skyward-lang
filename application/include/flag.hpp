#pragma once
#include "common.hpp"
#include "error.hpp"

class Flag {
public:
    string name;
    vector<string> flags;
    string desc;
    bool attr;

public:
    Flag(const string name, const vector<string>& flags, const string desc, bool attr);
    
    bool has(string word);
    int size();

    void print();

    void update();
};