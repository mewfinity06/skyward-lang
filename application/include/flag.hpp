#pragma once
#include "common.hpp"
#include "error.hpp"

// TODO: make `attr` to hold any value 
//     | may have to seperate into different classes
//     | i.e. having a class for bool attrs, int attrs, etc
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