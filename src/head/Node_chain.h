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

	//�������н��
	int chain_all_num;
	vector<string*> chain_all;
	//�����֧ǰ�����н��
	vector<vector<string*>> cur_chain_all_list;
	//���浱ǰ��֮ǰ�����н��
	vector<string*> cur_chain_all;

	//������൥�ʵĽ��
	vector<Node*> chain_word;
	//���������ĸ�Ľ��
	int chain_char_num;
	vector<Node*> chain_char;

	//���浱ǰ���ʵ����н��
	vector<string*> new_chain_all;
	//���浱ǰ������Ϣ
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

