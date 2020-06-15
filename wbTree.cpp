#include "wbTree.h"

wbTree::wbTree(Board* b, int p, int cid) {
	root = new TreeNode(b, p, cid);
}