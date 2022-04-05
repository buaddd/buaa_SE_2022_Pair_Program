#include "Checker.h"
using namespace std;

Checker::Checker() {
}

void Checker::setup(char** words, int len) {
	Generator* gen = new Generator(words, len);
	gen->get_nodes(nodes);
	gen->get_head_map(&start_map);
}

//���������л�
bool Checker::judge_circle() {
	int count = 0; //���ڼ����Ƿ��нڵ�ʣ��
	queue<Node*> node_queue;
	//�ҳ��������Ϊ0�Ľڵ�
	for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		Node* node = *it;
		if ((node->get_inDegree()) == 0) {
			node_queue.push(node);
			count++;
		}
		//ͬʱ�ж��Ƿ���ڶ������a....a�ĵ��ʣ���������ض��л�
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
		//��ǰ�ڵ��к�̽ڵ�
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