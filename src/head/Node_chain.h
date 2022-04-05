#pragma once
#include "Const.h"
#include "Node.h"
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Node_chain
{
private:
	bool all_flag;
	bool char_flag;

	//保存所有结果
	int chain_all_num;
	vector<string*> chain_all;
	//保存分支前的所有结果
	vector<vector<string*>> cur_chain_all_list;
	//保存当前点之前的所有结果
	vector<string*> cur_chain_all;

	//保存最多单词的结果
	vector<Node*> chain_word;
	//保存最多字母的结果
	int chain_char_num;
	vector<Node*> chain_char;

	//保存当前单词的所有结果
	vector<string*> new_chain_all;
	//保存当前链的信息
	int cur_chain_char_num;
	vector<Node*> cur_chain;

public:
	Node_chain();
	void init(bool, bool);

	void add_Node(Node*);
	void remove_last_node();

	void update_chain_all();
	void push_cur_chain_all_list();
	void pop_cur_chain_all_list();

	void update_chain_word();

	void update_chain_char();

	int get_chain_all_num();
	void get_chain_all(char**);
	int get_chain_char_num();
	void get_chain_char(char**);
	int get_chain_word_num();
	void get_chain_word(char**);

private:
	void update_cur_chain_all(Node*);
	void add_chain_all(string*, int);

};

