#include "Word_tarjan_vertex.h"
using namespace std;

Word_tarjan_vertex::Word_tarjan_vertex() {
	this->indgr = 0;
	this->outdgr = 0;
	this->visited_flag = false;

	this->word_vertex_set.clear();
	this->edge_set.clear();
}

/*
	�����
*/
void Word_tarjan_vertex::add_word(Word_vertex* wv) {
	this->word_vertex_set.insert(wv);
}

void Word_tarjan_vertex::get_word_set(set<Word_vertex*>& word_set_in) {
	word_set_in.clear();
	for (set<Word_vertex*>::iterator it = this->word_vertex_set.begin(); it != this->word_vertex_set.end(); it++) {
		word_set_in.insert(*it);
	}
}

/*
	�����
*/
void Word_tarjan_vertex::set_edges() {
	for (set<Word_vertex*>::iterator it = this->word_vertex_set.begin(); it != this->word_vertex_set.end(); it++) {
		set<Word_vertex*> word_set;
		(*it)->get_edges(word_set);

		for (set<Word_vertex*>::iterator jt = word_set.begin(); jt != word_set.end(); jt++) {
			if ((*jt)->get_word_tarjan_vertex() != this &&
				this->edge_set.count((*jt)->get_word_tarjan_vertex()) == 0) {
				this->edge_set.insert((*jt)->get_word_tarjan_vertex());
				this->add_outdgr();
				(*jt)->get_word_tarjan_vertex()->add_indgr();
			}
		}

	}
}

void Word_tarjan_vertex::get_edges(set<Word_tarjan_vertex*>& egde_set_in) {
	egde_set_in.clear();
	for (set<Word_tarjan_vertex*>::iterator it = this->edge_set.begin(); it != this->edge_set.end(); it++) {
		egde_set_in.insert(*it);
	}
}

/*
	dgr �����������������
*/
void Word_tarjan_vertex::add_indgr() {
	(this->indgr)++;
}

void Word_tarjan_vertex::add_outdgr() {
	(this->outdgr)++;
}

int Word_tarjan_vertex::get_indgr() {
	return this->indgr;
}

int Word_tarjan_vertex::get_outdgr() {
	return this->outdgr;
}

/*
	visited ��أ���������������
*/
bool Word_tarjan_vertex::is_visited() {
	return this->visited_flag;
}

void Word_tarjan_vertex::set_visited() {
	this->visited_flag = true;
}

void Word_tarjan_vertex::clear_visited() {
	this->visited_flag = false;
}