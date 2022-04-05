#include "Word_chain.h" 
using namespace std;

Word_chain::Word_chain() {
	this->chain_char.clear();
	this->chain_word.clear();
	this->chain_char_num = 0;
	this->chain_word_num = 0;

	this->cur_chain_word.clear();
	this->cur_chain_char.clear();
	this->cur_chain_char_num = 0;
	this->cur_chain_word_num = 0;

	this->cur_word_chain.clear();
	this->cur_word_chain_char_num = 0;
	this->cur_word_chain_word_num = 0;

	this->char_flag = false;
	this->head = '\0';
	this->tail = '\0';
}

void Word_chain::set_char_flag() {
	this->char_flag = true;
}

void Word_chain::set_head(char head_in) {
	this->head = head_in;
}

void Word_chain::set_tail(char tail_in) {
	this->tail = tail_in;
}

/*
	调用每个节点之前需要初始化
*/
void Word_chain::init() {
	this->cur_chain_word.clear();
	this->cur_chain_char.clear();
	this->cur_chain_char_num = 0;
	this->cur_chain_word_num = 0;

	this->cur_word_chain.clear();
	this->cur_word_chain_char_num = 0;
	this->cur_word_chain_word_num = 0;
}

void Word_chain::add_word(Word_vertex* wv, Word_tarjan_vertex* wtv) {
	this->cur_word_chain.push_back(wv);

	if (this->char_flag == true) {
		if (wv->get_word_tarjan_vertex() != wtv) {
			this->cur_word_chain_char_num += wv->get_chain_char_num();
		}
		else {
			this->cur_word_chain_char_num += wv->get_char_num();
		}
		
	}
	else {
		if (wv->get_word_tarjan_vertex() != wtv) {
			this->cur_word_chain_word_num += wv->get_chain_word_num();
		}
		else {
			this->cur_word_chain_word_num++;
		}
	}
}

void Word_chain::remove_last_word(Word_tarjan_vertex* wtv) {
	if (this->char_flag == true) {
		if (this->cur_word_chain.back()->get_word_tarjan_vertex() != wtv) {
			this->cur_word_chain_char_num -= this->cur_word_chain.back()->get_chain_char_num();
		}
		else {
			this->cur_word_chain_char_num -= this->cur_word_chain.back()->get_char_num();
		}
	}
	else {
		if (this->cur_word_chain.back()->get_word_tarjan_vertex() != wtv) {
			this->cur_word_chain_word_num -= this->cur_word_chain.back()->get_chain_word_num();
		}
		else {
			this->cur_word_chain_word_num--;
		}
	}

	this->cur_word_chain.pop_back();
}

/*
	用于检查在本连通子图中的点
*/
bool Word_chain::is_acceptable(Word_tarjan_vertex* wtv) {
	bool ok = false;

	for (vector<Word_vertex*>::iterator it = this->cur_word_chain.begin(); it != this->cur_word_chain.end(); it++) {
		if (!(*it)->is_visited() && (*it)->get_word_tarjan_vertex() == wtv) {
			ok = true;
			break;
		}
	}

	if (ok == false && (this->tail == '\0' || this->cur_word_chain.back()->get_tail() == this->tail)) {
		return true;
	}

	return false;
}

/*
	如果 tail != '\0'
	我们更新的 word_chain 一定是以 tail 结尾的！
	因为我们是按照拓扑逆序进行的
	换言之
	precondition
		cur_word_chain 的结尾是 tail
		但是我们没有保证 cur_word_chain 的 head 相同
		所以 update_chain_word/char() 需要判断 head
*/
void Word_chain::update_cur_chain_char() {
	if (this->cur_word_chain_char_num > this->cur_chain_char_num) {
		this->cur_chain_char.clear();
		for (vector<Word_vertex*>::iterator it = this->cur_word_chain.begin(); it != this->cur_word_chain.end(); it++) {
			this->cur_chain_char.push_back(*it);
		}
		this->cur_chain_char_num = this->cur_word_chain_char_num;

		this->cur_chain_char.front()->set_word_chain(this->cur_chain_char, this->cur_chain_char_num, this->cur_chain_word_num);
	}

	this->update_chain_char();
}

void Word_chain::update_cur_chain_word() {
	if (this->cur_word_chain_word_num > this->cur_chain_word_num) {
		this->cur_chain_word.clear();
		for (vector<Word_vertex*>::iterator it = this->cur_word_chain.begin(); it != this->cur_word_chain.end(); it++) {
			this->cur_chain_word.push_back(*it);
		}
		this->cur_chain_word_num = this->cur_word_chain_word_num;

		this->cur_chain_word.front()->set_word_chain(this->cur_chain_word, this->cur_chain_char_num, this->cur_chain_word_num);
	}
	
	this->update_chain_word();
}

void Word_chain::update_chain_char() {
	if (this->cur_word_chain_char_num > this->chain_char_num &&
		(this->cur_word_chain.front()->get_head() == this->head || this->head == '\0')) {
		this->chain_char.clear();
		for (vector<Word_vertex*>::iterator it = this->cur_word_chain.begin(); it != this->cur_word_chain.end(); it++) {
			this->chain_char.push_back(*it);
		}
		this->chain_char_num = this->cur_word_chain_char_num;
	}
}

void Word_chain::update_chain_word() {
	if (this->cur_word_chain_word_num > this->chain_word_num &&
		(this->cur_word_chain.front()->get_head() == this->head || this->head == '\0')) {
		this->chain_word.clear();
		for (vector<Word_vertex*>::iterator it = this->cur_word_chain.begin(); it != this->cur_word_chain.end(); it++) {
			this->chain_word.push_back(*it);
		}
		this->chain_word_num = this->cur_word_chain_word_num;
	}
}

int Word_chain::get_chain_word_num() {
	return this->chain_word_num;
}

int Word_chain::get_chain_char_num() {
	return this->chain_char.size();
}

/*
	while 实现
*/
void Word_chain::get_chain_word(char** result) {
	if (this->chain_word_num <= MAX_CHAIN_ALL_SIZE && this->chain_word_num > 0) {
		int cnt = 0;
		vector<Word_vertex*>* word_setp = &(this->chain_word);
		while (true) {
			vector<Word_vertex*>::iterator it;

			if (word_setp->front()->get_word_tarjan_vertex() == word_setp->back()->get_word_tarjan_vertex()) {
				for (it = word_setp->begin(); it != word_setp->end(); it++) {
					result[cnt] = (char*)((*it)->get_string()->c_str());
					cnt++;
				}
				break;
			}
			else {
				for (it = word_setp->begin(); it != word_setp->end() - 1; it++) {
					result[cnt] = (char*)((*it)->get_string()->c_str());
					cnt++;
				}
				word_setp = (*it)->get_word_chainp();
			}
		}
	}
	else {
		result = NULL;
	}
}

void Word_chain::get_chain_char(char** result) {
	if (this->chain_char_num <= MAX_CHAIN_ALL_SIZE && this->chain_char_num > 0) {
		int cnt = 0;
		vector<Word_vertex*>* word_setp = &(this->chain_char);
		while (true) {
			vector<Word_vertex*>::iterator it;

			if (word_setp->front()->get_word_tarjan_vertex() == word_setp->back()->get_word_tarjan_vertex()) {
				for (it = word_setp->begin(); it != word_setp->end(); it++) {
					result[cnt] = (char*)((*it)->get_string()->c_str());
					cnt++;
				}
				break;
			}
			else {
				for (it = word_setp->begin(); it != word_setp->end() - 1; it++) {
					result[cnt] = (char*)((*it)->get_string()->c_str());
					cnt++;
				}
				word_setp = (*it)->get_word_chainp();
			}
		}
	}
	else {
		result = NULL;
	}
}

