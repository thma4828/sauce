#pragma once
#include "Node.h"
class Tree
{
public:
	Tree();
	Tree(Node*);
	Node* root;
	Node* curr_move;
	Node* curr_node;

	int calculate_move_white();
};

