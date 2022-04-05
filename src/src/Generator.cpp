#include "Generator.h"
using namespace std;

Generator::Generator(char** words, int len) {
    for (int i = 0; i < len; i++) {
        Generator::words.push_back(words[i]);
    }
}

//将去重后的字符串转化为node进行保存
void Generator::build_nodes() {
    vector<string>::iterator it;
    for (it = words.begin(); it != words.end(); it++) {
        string* word = new string(*it);
        char start = (*word)[0];
        char end = (*word)[word->length() - 1];
        char keys[2];
        keys[0] = start;
        keys[1] = end;
        string key(keys, keys + 2);
        //同类型节点已经存在，则加入对应节点的列表
        if (start_end_map.count(key) > 0) {
            start_end_map[key]->add_to_list(word);
            continue;
        }
        //新建该类型的节点
        Node* node = new Node(start, end);
        node->add_to_list(word);
        //更新对应节点的入度
        if (end_map.count(start) > 0) {
            vector<Node*> temp = end_map[start];
            int size = (int)temp.size();
            for (int i = 0; i < size; i++) {
                node->add_inDegree();
                temp[i]->add_out(node);
            }
        }
        if (start_map.count(end) > 0) {
            vector<Node*> temp = start_map[end];
            for (vector<Node*>::iterator iter = temp.begin(); iter != temp.end(); iter++) {
                Node* temp_node = *iter;
                temp_node->add_inDegree();
                node->add_out(temp_node);
            }
        }
        //维护三个map
        if (start_map.count(start) > 0) {
            start_map[start].push_back(node);
        }
        else {
            vector<Node*> new_vector;
            new_vector.push_back(node);
            start_map[start] = new_vector;
        }

        if (end_map.count(end) > 0) {
            end_map[end].push_back(node);
        }
        else {
            vector<Node*> new_vector;
            new_vector.push_back(node);
            end_map[end] = new_vector;
        }
        start_end_map[key] = node;
        nodes.push_back(node);
        //cout << *it << endl;
    }
}

void Generator::build_words() {
    vector<string>::iterator it;
    for (it = words.begin(); it != words.end(); it++) {
        string* word = new string(*it);
        char start = (*word)[0];
        char end = (*word)[word->length() - 1];
        //新建该类型的节点
        Word_vertex* vertex = new Word_vertex(word, start, end, (int)word->length());
        //更新图
        if (end_map_r.count(start) > 0) {
            vector<Word_vertex*> temp = end_map_r[start];
            int size = (int)temp.size();
            for (int i = 0; i < size; i++) {
                temp[i]->add_edge(vertex);
            }
        }
        if (start_map_r.count(end) > 0) {
            vector<Word_vertex*> temp = start_map_r[end];
            for (vector<Word_vertex*>::iterator iter = temp.begin(); iter != temp.end(); iter++) {
                vertex->add_edge(*iter);
            }
        }
        //维护三个map
        if (start_map_r.count(start) > 0) {
            start_map_r[start].push_back(vertex);
        }
        else {
            vector<Word_vertex*> new_vector;
            new_vector.push_back(vertex);
            start_map_r[start] = new_vector;
        }

        if (end_map_r.count(end) > 0) {
            end_map_r[end].push_back(vertex);
        }
        else {
            vector<Word_vertex*> new_vector;
            new_vector.push_back(vertex);
            end_map_r[end] = new_vector;
        }
        my_word_vertex.push_back(vertex);
        //cout << *it << endl;
    }
}

void Generator::clear() {
    start_map.clear();
    end_map.clear();
    start_map_r.clear();
    end_map_r.clear();
    start_end_map.clear();
    for (int i = 0; i < nodes.size(); i++) {
        delete nodes[i];
    }
    nodes.clear();
    for (int i = 0; i < my_word_vertex.size(); i++) {
        delete my_word_vertex[i];
    }
    my_word_vertex.clear();
}


void Generator::get_nodes(vector<Node*>& list) {
    list.assign(nodes.begin(), nodes.end());
}

void Generator::get_Word_vertex_set(set<Word_vertex*>& word_vertex_set_in) {
    vector<Word_vertex*>::iterator it;
    for (it = my_word_vertex.begin(); it != my_word_vertex.end(); it++) {
        word_vertex_set_in.insert(*it);
    }
}

void Generator::get_head_map(map<char, vector<Node*>>* result) {
    copy(start_map.begin(), start_map.end(), inserter(*result, result->begin()));
}