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



valIndex Tree::get_min(vector<float>f){
	int s = f.size();
	float min = f[0];
	int i = 0;
	for(int j=1; j<s; j++){
		if(f[j] < min){
			min = f[j]
			i = j
		}
	}
	return valIndex(min, i);
}

valIndex Tree::get_max(vector<float>f){
	int s = f.size();
	float max = f[0];
	int i = 0;
	for(int j=1; j<s; j++){
		if(f[j] > max){
			max = f[j]
			i = j
		}
	}
	return valIndex(max, i);
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
		valIndex vi = get_max(get_vals(curr));
		curr->wb_ratio = vi.value;
		curr->best_child = curr->children[vi.index];
		return;
	}
	if(depth < max){
		for (int i = 0; i < curr->children.size(); i++) {
			Node *ni = curr->children[i];
			eval_tree_white(ni, depth++, max, (wb + 1) % 2, 0);
		}
		if(wb == 1){
			valIndex vi = get_min(get_vals(curr));
			curr->wb_ratio = vi.value;
			curr->best_child = curr->children[vi.index];
		}else{
			valIndex vi = get_max(get_vals(curr));
			curr->wb_ratio = vi.value;
			curr->best_child = curr->children[vi.index];
		}

	}else{
		if(wb == 1){
			curr->wb_ratio = get_min(get_vals(curr));
		}else{
			curr->wb_ratio = get_max(get_vals(curr));
		}
	}
}
