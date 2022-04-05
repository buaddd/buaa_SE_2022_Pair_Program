#ifndef __word_chain_builder_h__
#define __word_chain_builder_h__
#include "Word_chain.h"
#include "Word_graph.h"
#include "Word_tarjan_vertex.h"
#include "Word_vertex.h"
#include <set>
using namespace std;

class Word_vertex;
class Word_graph;
class Word_chain;
class Word_tarjan_vertex;
class Word_chain_builder
{
private:
	int build_type;

	//����ͼ
	Word_graph word_graph;
	//������
	Word_chain word_chain;
	//tarjan ͼ
	set<Word_tarjan_vertex*> tarjan_set;

	Word_tarjan_vertex* next_tarjan_vertex();
	void travelsal_build(Word_vertex*, Word_tarjan_vertex*);
public:
	Word_chain_builder();

	void init(int, char, char, char**, int);
	void build();

	int get_num();
	void get_result(char**);
};
#endif

