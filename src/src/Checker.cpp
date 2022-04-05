#include "Checker.h"
using namespace std;

Checker::Checker() {
}

void Checker::setup(char** words, int len) {
	Generator* gen = new Generator(words, len);
	gen->build_nodes();
	gen->get_nodes(nodes);
	gen->get_head_map(&start_map);
}

//拓扑排序判环
bool Checker::judge_circle() {
	int count = 0; //用于计算是否还有节点剩余
	queue<Node*> node_queue;
	//找出所有入度为0的节点
	for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		Node* node = *it;
		if ((node->get_inDegree()) == 0) {
			node_queue.push(node);
			count++;
		}
		//同时判断是否存在多个形如a....a的单词，若存在则必定有环
		if (node->get_head() == node->get_tail()) {
			vector<string*> temp_vector;
			node->get_list(temp_vector);
			if (temp_vector.size() > 1) {
				return false;
			}
		}
	}
	//cout << "start" << endl;
	while (!node_queue.empty()) {
		Node* temp = node_queue.front();
		//temp->show_words();
		node_queue.pop();
		char end = temp->get_tail();
		//当前节点有后继节点
		if (start_map.count(end) > 0) {
			vector<Node*> list = start_map[end];
			for (vector<Node*>::iterator iter = list.begin(); iter != list.end(); iter++) {
				Node* node = *iter;
				node->sub_inDegree();
				if (node->get_inDegree() == 0) {
					//cout << "next node: " << endl;
					//node->show_words();
					node_queue.push(node);
					count++;
				}
			}
		}
	}
	//cout << count << endl;
	return count == nodes.size();
}
