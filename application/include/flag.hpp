#pragma once
#include "common.hpp"
#include "error.hpp"

class Flag {
public:
    vector<string> flags;
    string desc;
    void* attr;

public:
    Flag(const vector<string>& flags, const string desc, void* attr);
    
    bool has(string word);
    int size();

    void print();

    void update(void* new_attr);
};