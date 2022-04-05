#include "Core.h"
#include "Node_chain_builder.h"
#include "Node_chain.h"
using namespace std;

int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	if (enable_loop == false) {
		this->node_chain_builder.init(WORD_TYPE, words, len);
		this->node_chain_builder.build(head, tail);
		this->node_chain_builder.get_result(result);
		return this->node_chain_builder.get_num();
	}
	else {
		this->word_chain_builder.init(WORD_TYPE, head, tail, words, len);
		this->word_chain_builder.build();
		this->word_chain_builder.get_result(result);
		return this->word_chain_builder.get_num();
	}
}

int Core::gen_chains_all(char* words[], int len, char* result[])
{
	this->node_chain_builder.init(ALL_TYPE, words, len);
	this->node_chain_builder.build('\0', '\0');
	this->node_chain_builder.get_result(result);
	return this->node_chain_builder.get_num();
}

int Core::gen_chain_word_unique(char* words[], int len, char* result[])
{
	this->node_chain_builder.init(WORD_UNI_TYPE, words, len);
	this->node_chain_builder.build('\0', '\0');
	this->node_chain_builder.get_result(result);
	return this->node_chain_builder.get_num();
}

int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	if (enable_loop == false) {
		this->node_chain_builder.init(CHAR_TYPE, words, len);
		this->node_chain_builder.build(head, tail);
		this->node_chain_builder.get_result(result);
		return this->node_chain_builder.get_num();
	}
	else {
		this->word_chain_builder.init(CHAR_TYPE, head, tail, words, len);
		this->word_chain_builder.build();
		this->word_chain_builder.get_result(result);
		return this->word_chain_builder.get_num();
	}
}
