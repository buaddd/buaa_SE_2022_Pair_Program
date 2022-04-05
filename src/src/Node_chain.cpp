#include "Node_chain.h"
using namespace std;

Node_chain::Node_chain() {
	this->all_flag = false;
	this->char_flag = false;

	this->chain_all_num = 0;
	this->chain_all.clear();
	this->cur_chain_all_list.clear();
	this->cur_chain_all.clear();

	this->chain_word.clear();
	this->chain_char_num = 0;
	this->chain_char.clear();

	this->new_chain_all.clear();
	this->cur_chain_char_num = 0;
	this->cur_chain.clear();
}

void Node_chain::init(bool all_flag_in, bool char_flag_in) {
	this->all_flag = all_flag_in;
	this->char_flag = char_flag_in;

	this->cur_chain_all.push_back(new string(""));
}


void Node_chain::add_Node(Node* node) {
	node->set_vis();

	if (this->all_flag == true) {
		this->update_cur_chain_all(node);
	}
	else {
		this->cur_chain.push_back(node);
		if (this->char_flag == true) {
			this->cur_chain_char_num += node->get_longest_length();
		}
	}
}

void Node_chain::remove_last_node() {
	if (this->char_flag == true) {
		this->cur_chain_char_num -= this->cur_chain.back()->get_longest_length();
	}
	this->cur_chain.pop_back();
}

/*
	读取到一个新的 Node 后
	根据 Node 中 word_list 和 cur_chain_all 生成 new_chain_all
	然后把 new_chain_all 更新到 cur_chain_all中
	清空 new_chain_all
*/
void Node_chain::update_cur_chain_all(Node* node) {
	for (vector<string*>::reverse_iterator it = this->cur_chain_all.rbegin(); it != this->cur_chain_all.rend(); it++) {
		vector<string*> word_list;
		node->get_list(word_list);

		if ((*it)->compare("") != 0 && (*it)->at((*it)->length() - 1) != node->get_head()) {
			continue;
		}

		for (vector<string*>::iterator jt = word_list.begin(); jt != word_list.end(); jt++) {
			string* chain_new;
			if ((*it)->compare("") == 0) {
				chain_new = new string("*");
			}
			else {
				if ((*it)->at(0) == '*') {
					chain_new = new string((*it)->substr(1));
				}
				else {
					chain_new = new string(**it);
				}
				chain_new->append(" ");
			}
			chain_new->append(**jt);
			this->new_chain_all.push_back(chain_new);
		}
	}

	this->cur_chain_all.insert(this->cur_chain_all.end(), this->new_chain_all.begin(), this->new_chain_all.end());
	this->new_chain_all.clear();
}

/*
	当读取到一个结束的标志时
	根据 cur_chain_all 和 cur_chain_all_list 得到单词链
	更新 chain_all
	清空 cur_chain_all
	并把""加入到 cur_chain_all

	涉及 add_chain_all() 这个递归函数
*/
void Node_chain::update_chain_all() {
	for (vector<string*>::iterator it = this->cur_chain_all.begin(); it != this->cur_chain_all.end(); it++) {
		if ((*it)->compare("") != 0 && (*it)->at(0) != '*') {
			this->add_chain_all(*it, (int)this->cur_chain_all_list.size() - 1);
		}
	}

	this->cur_chain_all.clear();
	this->cur_chain_all.push_back(new string(""));
}

void Node_chain::add_chain_all(string* cur_chain, int cnt) {
	if (cnt == -1) {
		if (this->chain_all_num <= MAX_CHAIN_ALL_SIZE) {
			this->chain_all.push_back(cur_chain);
		}
		
		this->chain_all_num++;
	}
	else {
		for (vector<string*>::iterator it = this->cur_chain_all_list.at(cnt).begin();
			it != this->cur_chain_all_list.at(cnt).end(); it++) {
			string cur_chain_new(**it);
			cur_chain_new.append(*cur_chain);
			add_chain_all(&cur_chain_new, cnt - 1);
		}
	}
}

/*
	维护 cur_chain_all_list
*/
void Node_chain::push_cur_chain_all_list() {
	this->cur_chain_all_list.push_back(this->cur_chain_all);
	this->cur_chain_all.clear();
	this->cur_chain_all.push_back(new string(""));
}

void Node_chain::pop_cur_chain_all_list() {
	this->cur_chain_all_list.pop_back();
}


void Node_chain::update_chain_word() {
	if (this->cur_chain.size() > this->chain_word.size()) {
		this->chain_word.clear();
		for (vector<Node*>::iterator it = this->cur_chain.begin(); it != this->cur_chain.end(); it++) {
			this->chain_word.push_back(*it);
		}
	}
}


void Node_chain::update_chain_char() {
	if (this->cur_chain_char_num > this->chain_char_num) {
		this->chain_char_num = this->cur_chain_char_num;
		this->chain_char.clear();
		for (vector<Node*>::iterator it = this->cur_chain.begin(); it != this->cur_chain.end(); it++) {
			this->chain_char.push_back(*it);
		}
	}
}

int Node_chain::get_chain_all_num() {
	return this->chain_all_num;
}

void Node_chain::get_chain_all(char** result) {
	if (this->chain_all_num <= MAX_CHAIN_ALL_SIZE) {
		int cnt = 0;
		for (vector<string*>::iterator it = this->chain_all.begin(); it != this->chain_all.end(); it++, cnt++) {
			result[cnt] = (char*)((*it)->c_str());
		}
	}
	else {
		result = NULL;
	}
}

int Node_chain::get_chain_char_num() {
	return this->chain_char_num;
}

void Node_chain::get_chain_char(char** result) {
	if (this->chain_char.size() <= MAX_CHAIN_ALL_SIZE) {
		int cnt = 0;
		for (vector<Node*>::iterator it = this->chain_char.begin(); it != this->chain_char.end(); it++, cnt++) {
			result[cnt] = (char*)((*it)->get_longest()->c_str());
		}
	}
	else {
		result = NULL;
	}
	
}

int Node_chain::get_chain_word_num() {
	return (int) this->chain_word.size();
}

void Node_chain::get_chain_word(char** result) {
	if (this->chain_char.size() <= MAX_CHAIN_ALL_SIZE) {
		int cnt = 0;
		for (vector<Node*>::iterator it = this->chain_word.begin(); it != this->chain_word.end(); it++, cnt++) {
			result[cnt] = (char*)((*it)->get_longest()->c_str());
		}
	}
	else {
		result = NULL;
	}
	
}