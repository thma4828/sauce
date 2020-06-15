#pragma once
#include "TreeNode.h"
#include "Piece.h"
#include <vector>
#include "Board.h"
using namespace std;


class wbTree
{
public:
	wbTree(Board*, int, int);
private:
	TreeNode* root;
	vector<int>cid_list;
};

