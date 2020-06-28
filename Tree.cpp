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

float Tree::get_min(vector<float>f){
	int s = f.size();
	float min = f[0];
	for(int j=1; j<s; j++){
		if(f[j] < min){
			min = f[j]
		}
	}
	return min;
}

float Tree::get_max(vector<float>f){
	int s = f.size();
	float max = f[0];
	for(int j=1; j<s; j++){
		if(f[j] > max){
			max = f[j]
		}
	}
	return max;
}

vector<float> Tree::get_vals(Node *ni){
	vector<float>wbs;
	for (int k = 0; k < ni->children.size(); k++) {
			Node *child_k = ni->chilldren[k]; //current move black could make.
			float wb_ik = child_k->wb_ratio;
			wbs.push_back(wb_ik);
	}
	return wbs;
}
//white code 0 black code 1
void Tree::eval_tree_white(Node *r, int depth, int max, int wb, int isr) {

	Node* curr = r;

	if(isr){
		for(int i=0; i<curr->children.size(); i++){
			eval_tree_white(curr->children[i], depth++, max, 1, 0)
		}
		curr->wb_ratio = get_max(get_vals(curr));
		return;
	}
	if(depth < max){
		for (int i = 0; i < curr->children.size(); i++) {
			Node *ni = curr->children[i];
			if(wb == 1){ //blacks move
				  for(int j=0; j<ni->children.size(); j++){
						 Node *nij = ni->chidren[j];
						 eval_tree(nij, depth++, max, 0, 0);
				  }
			 	  ni->wb_ratio = get_min(get_vals(ni)); //blacks best move
			}else{ //whites move
					for(int z=0; z<ni->children.size(); z++){
						Node *nij = ni->chidren[j];
						eval_tree(nij, depth++, max, 1, 0);
					}
					ni->wb_ratio = get_max(get_vals(ni)); //whites best move.
			}
		}
	}else{
		return; //depth of max has been reached so the algorithm halts further analys.
	}
}
