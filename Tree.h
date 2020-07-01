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

	void eval_tree_white(Node *, int, int, int, bool);
};

#endif //TREE_H
