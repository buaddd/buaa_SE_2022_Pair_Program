#ifndef __word_tarjan_vertex_h__
#define __word_tarjan_vertex_h__
#include "Word_vertex.h"
#include <set>
using namespace std;

class Word_vertex;
class Word_tarjan_vertex
{
private:
	int indgr;
	int outdgr;
	bool visited_flag;

	set<Word_vertex*> word_vertex_set;
	set<Word_tarjan_vertex*> edge_set;
public:
	Word_tarjan_vertex();

	void add_word(Word_vertex*);
	void get_word_set(set<Word_vertex*>&);

	void set_edges();
	void get_edges(set<Word_tarjan_vertex*>&);

	void add_indgr();
	void add_outdgr();
	int get_indgr();
	int get_outdgr();

	bool is_visited();
	void set_visited();
	void clear_visited();
};
#endif

