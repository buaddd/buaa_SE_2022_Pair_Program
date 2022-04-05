#include "Word_graph.h"
using namespace std;

Word_graph::Word_graph() {
	this->timestamp_cnt = 0;
	while (!(this->word_stack.empty())) {
		this->word_stack.pop();
	}

	this->word_tarjan_set.clear();
	this->word_set.clear();
}

void Word_graph::make_graph(Generator* generator) {
	generator->build_words();
	generator->get_Word_vertex_set(this->word_set);
}

void Word_graph::make_tarjan_word_graph() {
	this->timestamp_cnt = 1;
	this->word_tarjan_set.clear();
	for (set<Word_vertex*>::iterator it = this->word_set.begin(); it != this->word_set.end(); it++) {
		(*it)->clear_timestamp();
		(*it)->clear_visited();
	}

	for (set<Word_vertex*>::iterator it = this->word_set.begin(); it != this->word_set.end(); it++) {
		if ((*it)->get_word_tarjan_vertex() == NULL) {
			this->travelsal_tarjan((*it));
		}
	}

	for (set<Word_tarjan_vertex*>::iterator it = this->word_tarjan_set.begin(); it != this->word_tarjan_set.end(); it++) {
		(*it)->set_edges();
	}
}

void Word_graph::travelsal_tarjan(Word_vertex* wv) {
	wv->set_timestamp(this->timestamp_cnt);
	this->timestamp_cnt++;
	wv->set_visited();
	this->word_stack.push(wv);

	set<Word_vertex*> edge_set;
	wv->get_edges(edge_set);

	for (set<Word_vertex*>::iterator it = edge_set.begin(); it != edge_set.end(); it++) {
		if ((*it)->get_timestamp() == 0) {
			this->travelsal_tarjan(*it);

			if ((*it)->get_father_timestamp() < wv->get_father_timestamp()) {
				wv->update_father_timestamp((*it)->get_father_timestamp());
			}
		}
		else if ((*it)->is_visited()) {
			if ((*it)->get_timestamp() < wv->get_father_timestamp()) {
				wv->update_father_timestamp((*it)->get_timestamp());
			}
		}
	}

	if (wv->get_father_timestamp() == wv->get_timestamp()) {
		Word_tarjan_vertex* new_word_tarjan_vertex = new Word_tarjan_vertex();
		new_word_tarjan_vertex->add_word(wv);
		wv->clear_visited();
		wv->set_word_tarjan_vertex(new_word_tarjan_vertex);

		while (this->word_stack.top() != wv) {
			new_word_tarjan_vertex->add_word(this->word_stack.top());
			this->word_stack.top()->clear_visited();
			this->word_stack.top()->set_word_tarjan_vertex(new_word_tarjan_vertex);
			this->word_stack.pop();
		}
		this->word_stack.pop();

		this->word_tarjan_set.insert(new_word_tarjan_vertex);
	}
}

void Word_graph::get_tarjan_vertex_graph(set<Word_tarjan_vertex*>& tarjan_set) {
	tarjan_set.clear();
	for (set<Word_tarjan_vertex*>::iterator it = this->word_tarjan_set.begin(); it != this->word_tarjan_set.end(); it++) {
		tarjan_set.insert(*it);
	}
}