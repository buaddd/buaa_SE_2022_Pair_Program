#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <set>
#include <map>
using namespace std;

class MyIO
{
private:
    string readPath;
    string writePath;
    unordered_set<string>words;

public:
    MyIO(string readPath);
    void read_file();
    void write_file(bool, char**, int);
    int get_all_words(char**);
};

