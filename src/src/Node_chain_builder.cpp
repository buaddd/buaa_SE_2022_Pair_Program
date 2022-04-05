#include "Node_chain_builder.h"
#include "Node_chain.h"
using namespace std;

Node_chain_builder::Node_chain_builder() {
	this->build_type = -1;
	this->unique_flag = false;
	this->head = '\0';
	this->tail = '\0';
}

void Node_chain_builder::init(int build_type_in, char** words, int len) {
	Generator generator(words, len);
	this->node_graph.make_graph(&generator);

	this->build_type = build_type_in;

	switch (this->build_type) {
		case WORD_TYPE: {
			this->node_chain.init(false, false);
			this->unique_flag = false;

			break;
		}
		case WORD_UNI_TYPE: {
			this->node_chain.init(false, false);
			this->unique_flag = true;

			break;
		}
		case CHAR_TYPE: {
			this->node_chain.init(false, true);
			this->unique_flag = false;

			break;
		}
		case ALL_TYPE: {
			this->node_chain.init(true, false);
			this->unique_flag = false;

			break;
		}
	}
	
}

int Node_chain_builder::get_num() {
	switch (this->build_type) {
		case WORD_TYPE: {
			return this->node_chain.get_chain_word_num();
		}
		case WORD_UNI_TYPE: {
			return this->node_chain.get_chain_word_num();
		}
		case CHAR_TYPE: {
			return this->node_chain.get_chain_char_num();
		}
		case ALL_TYPE: {
			return this->node_chain.get_chain_all_num();
		}
		default: {
			return 0;
		}
	}
}

void Node_chain_builder::get_result(char** result) {
	switch (this->build_type) {
		case WORD_TYPE: {
			this->node_chain.get_chain_word(result);
			return;
		}
		case WORD_UNI_TYPE: {
			this->node_chain.get_chain_word(result);
			return;
		}
		case CHAR_TYPE: {
			this->node_chain.get_chain_char(result);
			return;
		}
		case ALL_TYPE: {
			this->node_chain.get_chain_all(result);
			return;
		}
	}
}

/*
	这里需要写一个枚举开始节点，注意再 chain_all 时 ht 不起作用
*/
void Node_chain_builder::build(char head_in, char tail_in) {
	this->head = head_in;
	this->tail = tail_in;
	Node* next_nodep = NULL;


	while ((next_nodep = this->node_graph.next_node(this->head)) != NULL) {
		this->travelsal_build(next_nodep);
	}
}

void Node_chain_builder::travelsal_build(Node* node) {
	this->node_chain.add_Node(node);

	switch (this->build_type) {
		case WORD_TYPE: {
			word_type_chain_builder(node);
			this->node_chain.remove_last_node();
			break;
		}
		case WORD_UNI_TYPE: {
			word_type_chain_builder(node);
			this->node_chain.remove_last_node();
			break;
		}
		case CHAR_TYPE: {
			char_type_chain_builder(node);
			this->node_chain.remove_last_node();
			break;
		}
		case ALL_TYPE: {
			all_type_chain_builder(node);
			break;
		}
	}
}

void Node_chain_builder::word_type_chain_builder(Node* node) {
	vector<Node*> node_out_list;
	node->get_out(node_out_list);
	//除首尾字母相同之外的 out 的数量
	int list_len = 0;
	Node* repeated_node = NULL;

	if (this->build_type == WORD_UNI_TYPE && node->get_head() == node->get_tail()) {
		this->node_chain.update_chain_char();
		return;
	}

	for (vector<Node*>::iterator it = node_out_list.begin(); it != node_out_list.end(); it++) {
		if ((*it)->get_head() == (*it)->get_tail()) {
			repeated_node = *it;
			break;
		}
	}
	if (repeated_node != NULL) {
		if (this->build_type == WORD_TYPE) {
			this->node_chain.add_Node(repeated_node);
		}
		list_len = (int) node_out_list.size() - 1;
	}
	else {
		list_len = (int) node_out_list.size();
	}

	if (this->tail == node->get_tail()) {
		if (this->build_type == WORD_UNI_TYPE && repeated_node != NULL) {
			this->node_chain.add_Node(repeated_node);
		}

		this->node_chain.update_chain_word();

		if (this->build_type == WORD_UNI_TYPE && repeated_node != NULL) {
			this->node_chain.remove_last_node();
		}
	}
	else if (list_len == 0 && this->tail == '\0') {
		if (this->build_type == WORD_UNI_TYPE && repeated_node != NULL) {
			this->node_chain.add_Node(repeated_node);
		}

		this->node_chain.update_chain_word();

		if (this->build_type == WORD_UNI_TYPE && repeated_node != NULL) {
			this->node_chain.remove_last_node();
		}
	}
	else {
		for (vector<Node*>::iterator it = node_out_list.begin(); it != node_out_list.end(); it++) {
			if ((*it)->get_head() == (*it)->get_tail()) {
				continue;
			}

			this->travelsal_build(*it);
		}
	}

	if (repeated_node != NULL && build_type == WORD_TYPE) {
		this->node_chain.remove_last_node();
	}
}

void Node_chain_builder::char_type_chain_builder(Node* node) {
	vector<Node*> node_out_list;
	node->get_out(node_out_list);
	//除首尾字母相同之外的 out 的数量
	int list_len = 0;
	Node* repeated_node = NULL;

	for (vector<Node*>::iterator it = node_out_list.begin(); it != node_out_list.end(); it++) {
		if ((*it)->get_head() == (*it)->get_tail()) {
			repeated_node = *it;
			break;
		}
	}
	if (repeated_node != NULL) {
		this->node_chain.add_Node(repeated_node);
		list_len = (int) node_out_list.size() - 1;
	}
	else {
		list_len = (int) node_out_list.size();
	}
	
	if (this->tail == node->get_tail()) {
		this->node_chain.update_chain_char();
	}
	else if (list_len == 0 && this->tail == '\0') {
		this->node_chain.update_chain_char();
	}
	else {
		for (vector<Node*>::iterator it = node_out_list.begin(); it != node_out_list.end(); it++) {
			if ((*it)->get_head() == (*it)->get_tail()) {
				continue;
			}

			this->travelsal_build(*it);
		}
	}

	if (repeated_node != NULL) {
		this->node_chain.remove_last_node();
	}
}

/*
	chain_all 不需要考虑 ht
*/
void Node_chain_builder::all_type_chain_builder(Node* node) {
	vector<Node*> node_out_list;
	node->get_out(node_out_list);

	if (node_out_list.size() == 0) {
		this->node_chain.update_chain_all();
	}
	else if (node_out_list.size() == 1) {
		this->travelsal_build(node_out_list.front());
	}
	else {
		this->node_chain.push_cur_chain_all_list();
		for (vector<Node*>::iterator it = node_out_list.begin(); it != node_out_list.end(); it++) {
			this->travelsal_build(*it);
		}
		this->node_chain.pop_cur_chain_all_list();
	}
}