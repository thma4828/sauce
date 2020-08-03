#ifndef TREE_H
#define TREE_H
#include "Node.h"
#include "Valindex.h"
#include <vector>
using namespace std;

class Valindex;

class Tree
{
public:
	Tree();
	Tree(Node*);
	Node* root;
	Node* curr_move;
	Node* curr_node;
	Valindex *get_min(vector<float>);
	Valindex *get_max(vector<float>);
	vector<float> get_vals(Node *);
};

#endif //TREE_H
