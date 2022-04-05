#pragma once
#include <vector>
#include <queue>
#include "Node.h"
#include "MyIO.h"
#include "Generator.h"

using namespace std;

class Checker
{
private:
	vector<Node*> nodes;
	map<char, vector<Node*>> start_map;
	Generator* gen;

public:
	Checker();
	void setup(char** words, int len);
	bool judge_circle();
};

