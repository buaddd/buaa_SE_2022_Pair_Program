#include "Node_graph.h"
Node_graph::Node_graph() {
	this->node_list.clear();
}

void Node_graph::make_graph(Generator* generator) {
	generator->build_nodes();
	generator->get_nodes(this->node_list);
}

Node* Node_graph::next_node(char head) {
	bool ok = true;
	int min_indgr = (int) this->node_list.size() + 1;
	Node* return_nodep = NULL;

	for (int i = 0; i < this->node_list.size(); i++) {
		if (this->node_list.at(i)->get_vis() == false && this->node_list.at(i)->get_inDegree() < min_indgr &&
			(head == '\0' || head == this->node_list.at(i)->get_head())) {
			ok = false;
			min_indgr = this->node_list.at(i)->get_inDegree();
			return_nodep = this->node_list.at(i);
		}
	}

	if (ok) {
		return NULL;
	}
	else {
		return return_nodep;
	}
}