#ifndef TREE_H
#define TREE_H
#include "Node.h"

class Tree
{
public:
	Tree();
	Tree(Node*);
	Node* root;
	Node* curr_move;
	Node* curr_node;
	float get_min(vector<float>);
	float get_max(vector<float>);
	vector<float> get_vals(Node *);

	void eval_tree_white(Node *, int, int, int, int);
};

#endif //TREE_H
