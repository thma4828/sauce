#pragma once
#include "Board.h"
#include <vector>
using namespace std;
class TreeNode {
public:
	TreeNode(Board*, int, int);

	void add_child(TreeNode*);

	Board* board;
	int parent_color;
	int child_id;
	vector<TreeNode*>children;
};