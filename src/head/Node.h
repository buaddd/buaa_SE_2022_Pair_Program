#pragma once
#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Node
{
private:
	char start;
	char end;
	//string word; //仅在-r时使用
	string* longest; //维护最多字母数量的单词
	vector<string*> word_list; //存储单词
	vector<Node*> out; //存储后驱节点
	int inDegree;
	bool vis;

public:
	Node(char start, char end);
	void set_vis();
	bool get_vis();
	char get_head();
	char get_tail();
	string* get_longest();
	int get_longest_length();
	void add_to_list(string*);
	void get_list(vector<string*>&);
	void add_inDegree();
	void sub_inDegree();
	int get_inDegree();
	void show_words();
	void add_out(Node*);
	void get_out(vector<Node*>&);
};
