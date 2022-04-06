#ifndef __word_chain__
#define __word_chain__
#include "Const.h"
#include "Word_vertex.h"
#include "Word_tarjan_vertex.h"
#include <vector>
#include <iostream>
using namespace std;

class Word_vertex;
class Word_tarjan_vertex;
class Word_chain {
private:
	//保存所有节点的最长路径
	int chain_word_num;
	vector<Word_vertex*> chain_word;
	int chain_char_num;
	vector<Word_vertex*> chain_char;

	//保存当前节点的最长路径
	vector<Word_vertex*> cur_chain_word;
	vector<Word_vertex*> cur_chain_char;
	int cur_chain_char_num;
	int cur_chain_word_num;

	//保存当前路径
	vector<Word_vertex*> cur_word_chain;
	int cur_word_chain_char_num;
	int cur_word_chain_word_num;

	bool char_flag;
	char head;
	char tail;

public:
	Word_chain();
	void set_char_flag();
	void set_head(char);
	void set_tail(char);

	void init();

	void add_word(Word_vertex*, Word_tarjan_vertex*);
	void remove_last_word(Word_tarjan_vertex*);

	bool is_acceptable(Word_tarjan_vertex*);

	void clear_cur_chain();
	void update_cur_chain_word();
	void update_cur_chain_char();
	void update_chain_word();
	void update_chain_char();

	int get_chain_word_num();
	void get_chain_word(char**);
	int get_chain_char_num();
	void get_chain_char(char**);
};
#endif