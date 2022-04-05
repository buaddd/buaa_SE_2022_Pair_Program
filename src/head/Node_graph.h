#pragma once
#include "Generator.h"
#include "Node.h"
#include <vector>
using namespace std;

class Node;
class Generator;
class Node_graph
{
private:
	vector<Node*> node_list;

public:
	Node_graph();
	void make_graph(Generator*);
	Node* next_node(char head);
};

