#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <set>
#include <map>
#include "Node.h"
#include "Word_vertex.h"
using namespace std;

class Generator
{
private:
    vector<Node*>nodes;
    vector<Word_vertex*>my_word_vertex;
    vector<string>words;
    map<char, vector<Node*>> start_map;
    map<char, vector<Node*>> end_map;
    map<char, vector<Word_vertex*>> start_map_r; //适用于-r情况下建立word
    map<char, vector<Word_vertex*>> end_map_r;
    map<string, Node*> start_end_map;

public:
    Generator(char**, int);
    void build_nodes();
    void build_words();
    void clear();
    void get_nodes(vector<Node*>&);
    void get_Word_vertex_set(set<Word_vertex*>&);
    void get_head_map(map<char, vector<Node*>>*);
};

