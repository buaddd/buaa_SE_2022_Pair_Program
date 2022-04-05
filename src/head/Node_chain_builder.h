#pragma once
#include "Node_chain.h"
#include "Node_graph.h"
#include "Generator.h"

class Node_chain_builder
{
private:
	int build_type;
	bool unique_flag;
	char head;
	char tail;

	Node_graph node_graph;
	Node_chain node_chain;

	void travelsal_build(Node*);
	void word_type_chain_builder(Node*);
	void char_type_chain_builder(Node*);
	void all_type_chain_builder(Node*);

public:
	Node_chain_builder();
	void init(int, char**, int);
	void build(char, char);
	void get_result(char**);
	int get_num();
};

