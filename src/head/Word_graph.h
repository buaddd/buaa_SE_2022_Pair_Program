#ifndef __word_graph_h__
#define __word_graph_h__
#include "Generator.h"
#include "Word_vertex.h"
#include "Word_tarjan_vertex.h"
#include <stack>
#include <set>
using namespace std;

class Word_vertex;
class Word_tarjan_vertex;
class Word_graph
{
private:
	//用于生成 tarjan 图
	int timestamp_cnt;
	stack<Word_vertex*> word_stack;

	//保存 tarjan 图
	set<Word_tarjan_vertex*> word_tarjan_set;
	//保存图
	set<Word_vertex*> word_set;

public:
	Word_graph();

	void make_graph(Generator*);
	void make_tarjan_word_graph();
	void get_tarjan_vertex_graph(set<Word_tarjan_vertex*>&);

private:
	void travelsal_tarjan(Word_vertex*);
};
#endif

