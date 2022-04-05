#include "Node.h"
using namespace std;

Node::Node(char start, char end) {
	Node::start = start;
	Node::end = end;
	Node::inDegree = 0;
	Node::longest = new string("a");
	Node::vis = false;
}

/*
//设置-r模式下此节点代表的单词
void set_word(string word) {
	Node::word = word;
}

//返回-r模式下此节点代表的单词
void get_word(string word) {
	word = Node::word;
}
*/

void Node::set_vis() {
	vis = true;
}

bool Node::get_vis() {
	return vis;
}

//返回开头的字母
char Node::get_head() {
	return Node::start;
}

//返回结尾的字母
char Node::get_tail() {
	return Node::end;
}

string* Node::get_longest() {
	return longest;
}

int Node::get_longest_length() {
	return (int)Node::longest->length();
}

//将单词插入列表
void Node::add_to_list(string* word) {
	Node::word_list.push_back(word);
	if (longest->length() < word->length()) {
		longest = word;
	}
	//cout << word << endl;
}

//复制单词列表
void Node::get_list(vector<string*>& list) {
	for (int i = 0; i < Node::word_list.size(); i++) {
		list.push_back(Node::word_list[i]);
	}
}

void Node::add_inDegree() {
	Node::inDegree++;
}

void Node::sub_inDegree() {
	Node::inDegree--;
}

int Node::get_inDegree() {
	return Node::inDegree;
}

void Node::show_words() {
	for (vector<string*>::iterator iter = word_list.begin(); iter != word_list.end(); iter++) {
		string* word = *iter;
		cout << (*word) << endl;
	}
}

void Node::add_out(Node* node) {
	out.push_back(node);
}

void Node::get_out(vector<Node*>& list) {
	for (int i = 0; i < Node::out.size(); i++) {
		list.push_back(Node::out[i]);
	}
}