#include "Word_chain_builder.h"
using namespace std;

Word_chain_builder::Word_chain_builder() {
	this->build_type = -1;

	this->tarjan_set.clear();
}

void Word_chain_builder::init(int chain_type_in, char head_in, char tail_in, char** words, int len) {
	Generator generator(words, len);

	this->build_type = chain_type_in;
	if (this->build_type == CHAR_TYPE) {
		this->word_chain.set_char_flag();
	}
	this->word_chain.set_head(head_in);
	this->word_chain.set_tail(tail_in);

	this->word_graph.make_graph(&generator);
	this->word_graph.make_tarjan_word_graph();
}

void Word_chain_builder::build() {
	this->word_graph.get_tarjan_vertex_graph(this->tarjan_set);
	Word_tarjan_vertex* wtv = NULL;

	while ((wtv = this->next_tarjan_vertex()) != NULL) {
		set<Word_vertex*> word_set;
		wtv->get_word_set(word_set);
		wtv->set_visited();

		for (set<Word_vertex*>::iterator it = word_set.begin(); it != word_set.end(); it++) {
				travelsal_build(*it, wtv);
		}
	}
}

void Word_chain_builder::travelsal_build(Word_vertex* wv, Word_tarjan_vertex* wtv) {
	wv->set_visited();
	this->word_chain.add_word(wv, wtv);

	if (wv->get_word_tarjan_vertex() != wtv) {
		if (wv->has_chain()) {
			if (this->build_type == CHAR_TYPE) {
				this->word_chain.update_cur_chain_char();
			}
			else {
				this->word_chain.update_cur_chain_word();
			}
		}
	}
	else {
		set<Word_vertex*> word_set;
		wv->get_edges(word_set);
		bool ok = false;
		for (set<Word_vertex*>::iterator it = word_set.begin(); it != word_set.end(); it++) {
			if (!(*it)->is_visited()) {
				travelsal_build((*it), wtv);
			}
		}

		if (this->word_chain.is_acceptable(wtv)) {
			if (this->build_type == CHAR_TYPE) {
				this->word_chain.update_cur_chain_char();
			}
			else {
				this->word_chain.update_cur_chain_word();
			}
		}
	}

	this->word_chain.remove_last_word(wtv);
	wv->clear_visited();
}

Word_tarjan_vertex* Word_chain_builder::next_tarjan_vertex() {
	int min_outdgr = (int) this->tarjan_set.size() + 1;
	Word_tarjan_vertex* return_wtv = NULL;

	for (set<Word_tarjan_vertex*>::iterator it = this->tarjan_set.begin(); it != this->tarjan_set.end(); it++) {
		if (!(*it)->is_visited() && (*it)->get_outdgr() < min_outdgr) {
			min_outdgr = (*it)->get_outdgr();
			return_wtv = (*it);
		}
	}

	return return_wtv;
}

int Word_chain_builder::get_num() {
	if (this->build_type == CHAR_TYPE) {
		return this->word_chain.get_chain_char_num();
	}
	else {
		return this->word_chain.get_chain_word_num();
	}
}

void Word_chain_builder::get_result(char** result) {
	if (this->build_type == CHAR_TYPE) {
		this->word_chain.get_chain_char(result);
	}
	else {
		this->word_chain.get_chain_word(result);
	}
}
