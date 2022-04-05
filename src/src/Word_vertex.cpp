#include "Word_vertex.h"
using namespace std;

Word_vertex::Word_vertex(string* str_in, char head_in, char tail_in, int char_num_in) {
	this->str = str_in;
	this->head = head_in;
	this->tail = tail_in;
	this->char_num = char_num_in;

	this->visited_flag = false;
	this->timestamp = 0;
	this->father_timestamp = 0;

	this->word_tarjan_vertex = NULL;
	this->word_vertex_set.clear();

	this->word_chain.clear();
	this->chain_char_num = 0;
	this->chain_word_num = 0;
}
/*
	�����
	�޸� word_vertex_set
*/
void Word_vertex::add_edge(Word_vertex* wv) {
	this->word_vertex_set.insert(wv);
}

void Word_vertex::get_edges(set<Word_vertex*>& edge_set) {
	for (set<Word_vertex*>::iterator it = this->word_vertex_set.begin(); it != this->word_vertex_set.end(); it++) {
		edge_set.insert(*it);
	}
}

/*
	visited_flag ���
	�������� tarjan ͼ
*/
bool Word_vertex::is_visited() {
	return this->visited_flag;
}

void Word_vertex::set_visited() {
	this->visited_flag = true;
}

void Word_vertex::clear_visited() {
	this->visited_flag = false;
}

/*
	timestamp ���
	�������� tarjan ͼ
*/
int Word_vertex::get_father_timestamp() {
	return this->father_timestamp;
}

int Word_vertex::get_timestamp() {
	return this->timestamp;
}

void Word_vertex::set_timestamp(int i) {
	this->timestamp = i;
	this->father_timestamp = i;
}

void Word_vertex::update_father_timestamp(int i) {
	this->father_timestamp = i;
}

void Word_vertex::clear_timestamp() {
	this->timestamp = 0;
	this->father_timestamp = 0;
}

/*
	���úͶ�ȡ���� tarjan ͼ�ڵ�
*/
void Word_vertex::set_word_tarjan_vertex(Word_tarjan_vertex* wtv) {
	this->word_tarjan_vertex = wtv;
}

Word_tarjan_vertex* Word_vertex::get_word_tarjan_vertex() {
	return this->word_tarjan_vertex;
}

/*
	���úͶ�ȡ�����Ϣ
*/
void Word_vertex::set_word_chain(vector<Word_vertex*>& word_chain_in, int chain_char_num_in, int chain_word_num_in) {
	for (vector<Word_vertex*>::iterator it = word_chain_in.begin(); it != word_chain_in.end(); it++) {
		this->word_chain.push_back(*it);
	}

	this->chain_char_num = chain_char_num_in;
	this->chain_word_num = chain_word_num_in;
}

int Word_vertex::get_chain_char_num() {
	return this->chain_char_num;
}

int Word_vertex::get_chain_word_num() {
	return this->chain_word_num;
}

//�����ж�һ���ڵ��Ƿ��з��϶���ĵ�����
bool Word_vertex::has_chain() {
	return !(this->chain_char_num == 0 && this->chain_word_num == 0);
}

//precndition һ�������з��϶���ĵ�����
vector<Word_vertex*>* Word_vertex::get_word_chainp() {
	return &(this->word_chain);
}

/*
	���ص�����Ϣ
*/
string* Word_vertex::get_string() {
	return this->str;
}

char Word_vertex::get_head() {
	return this->head;
}

char Word_vertex::get_tail() {
	return this->tail;
}

int Word_vertex::get_char_num() {
	return this->char_num;
}