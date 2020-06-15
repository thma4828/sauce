#include "TreeNode.h"
using namespace std;

TreeNode::TreeNode(Board* b, int p, int cid) {
	board = b;
	parent_color = p;
	child_id = cid;
}



void TreeNode::add_child(TreeNode* t) {
	children.push_back(t);
}
