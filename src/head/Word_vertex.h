#ifndef __word_vertex_h__
#define __word_vertex_h__
#include "Word_tarjan_vertex.h"
#include "Word_chain.h"
#include <vector>
#include <set>
#include <string>
using namespace std;

class Word_tarjan_vertex;
class Word_chain;
class Word_vertex
{
private:
	string* str;
	char head;
	char tail;
	int char_num;

	bool visited_flag;
	int timestamp;
	int father_timestamp;

	//所在 tarjan 节点
	Word_tarjan_vertex* word_tarjan_vertex;
	//所连接节点
	set<Word_vertex*> word_vertex_set;

	//以该结点为首的最长路径信息
	int chain_word_num;
	int chain_char_num;
	vector<Word_vertex*> word_chain;

public:
	Word_vertex(string*, char, char, int);
	void add_edge(Word_vertex*);
	void get_edges(set<Word_vertex*>&);

	bool is_visited();
	void set_visited();
	void clear_visited();

	int get_father_timestamp();
	int get_timestamp();
	void set_timestamp(int);
	void update_father_timestamp(int);
	void clear_timestamp();

	void set_word_tarjan_vertex(Word_tarjan_vertex*);
	Word_tarjan_vertex* get_word_tarjan_vertex();

	void set_word_chain(vector<Word_vertex*>&, int, int);
	int get_chain_char_num();
	int get_chain_word_num();
	bool has_chain();
	vector<Word_vertex*>* get_word_chainp();

	string* get_string();
	char get_head();
	char get_tail();
	int get_char_num();
};
#endif
