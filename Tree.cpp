#include "Tree.h"

Tree::Tree() {
	root = nullptr;
	curr_move = nullptr;
	curr_node = nullptr;
}

Tree::Tree(Node* r) {
	root = r;
	curr_node = r;
	curr_move = nullptr;
}

struct move {
	Node* n;
	float wb_ratio;
	int move_index;
};

int Tree::calculate_move_white() {
	Node* curr = root;
	float wb_curr = curr->wb_ratio;
	std::vector<move>moves; //each possible move gives rise to a branch to follow. 
	for (int j = 0; j < curr->children.size(); j++) {
		Node* child = curr->children[j];
		float wb_ratio_j = child->wb_ratio;
		move m;
		m.wb_ratio = wb_ratio_j;
		m.move_index = j;
		m.n = child;
		moves.push_back(m);
	}
	for (int i = 0; i < moves.size(); i++) {
		move m1 = moves[i];
		float thresh = curr->wb_ratio;
		for (int k = 0; k < m1.n->children.size(); k++) {
			float wb_ratio_ik = m1.n->white_value / m1.n->black_value;
			if (wb_ratio_ik < curr->wb_ratio) {
				moves[i].wb_ratio = wb_ratio_ik; //new value because on this branch black can force this value. 
				m1.n->wb_ratio = wb_ratio_ik; //change the value in the tree. 
			}
		}
	}
	move move_chosen = moves[0];
	for (int z = 1; z < moves.size(); z++) {
		move move_z = moves[z];
		if (move_z.wb_ratio > move_chosen.wb_ratio) {
			move_chosen = move_z;
		}
	}
}