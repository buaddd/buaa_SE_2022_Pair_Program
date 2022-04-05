#pragma once
#include "Node_chain_builder.h"
#include "Word_chain_builder.h"

using namespace std;
class Core
{
private:
	Node_chain_builder node_chain_builder;
	Word_chain_builder word_chain_builder;
	vector<Node*> node_list;

public:
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chains_all(char* words[], int len, char* result[]);
	int gen_chain_word_unique(char* words[], int len, char* result[]);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};