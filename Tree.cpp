
#include "Tree.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;




Tree::Tree(){
	root = NULL;
}

Tree::Tree(Node *r){
	root = r;
}


Valindex* Tree::get_min(vector<float>f){

	int s = f.size();
	if(s <= 0){
		return NULL;
	}
	float min = f[0];
	int i = 0;
	for(int j=1; j<s; j++){
		if(f[j] < min){
			min = f[j];
			i = j;
		}
	}
	Valindex *V = new Valindex();
	V->value = min;
	V->index = i;
	return V;
}

Valindex* Tree::get_max(vector<float>f){
	int s = f.size();
	if(s <= 0){
		return NULL;
	}
	float max = f[0];
	int i = 0;
	for(int j=1; j<s; j++){
		if(f[j] > max){
			max = f[j];
			i = j;
		}
	}
	Valindex *V = new Valindex();
	V->value = max;
	V->index = i;
	return V;
}

vector<float> Tree::get_vals(Node *ni){
	vector<float>wbs;
	for (int k = 0; k < ni->children.size(); k++) {
			Node *child_k = ni->children[k]; //current move black could make.
			float wb_ik = child_k->wb_ratio;
			wbs.push_back(wb_ik);
	}
	return wbs;
}
//white code 0 black code 1
void Tree::eval_tree_white(Node *r, int depth, int max, int wb, bool isr) {
	cout << "in eval_tree || Node: " << r << " || Depth: " << depth<< " || \n "
	<< "|| max: " << max << " || wb: " << wb << " || isr: " << isr << endl;
	Node* curr = r;

	if(isr){
		cout << "In root case." << endl;
		cout << "root position currently valued at: " << curr->wb_ratio << endl;
		cout << "root has: " << curr->children.size() << " children " << endl;
		for(int i=0; i<curr->children.size(); i++){
			eval_tree_white(curr->children[i], depth + 1, max, 1, false);
		}
		cout << "recursion has returned to root call." << endl;
		Valindex *vi = NULL;
	       	if(wb == BLACK)
		       vi = get_min(get_vals(curr));
		else if(wb == WHITE)
			vi = get_max(get_vals(curr));
		if(vi != NULL){
			curr->wb_ratio = vi->value;
			curr->best_child = curr->children[vi->index];
			cout << "position now valued at: " << curr->wb_ratio << endl;
		}

		return;
	}
	if(depth < max){
		cout << "in non-root case" << endl;
		for (int i = 0; i < curr->children.size(); i++) {
			Node *ni = curr->children[i];
			eval_tree_white(ni, depth + 1, max, (wb + 1) % 2, false);
		}
		cout << "non root eval" << endl;
		if(wb == BLACK){
			Valindex *vi = get_min(get_vals(curr));
			if(vi != NULL){
				curr->wb_ratio = vi->value;
				curr->best_child = curr->children[vi->index];
			}

		}else if(wb == WHITE){
			Valindex *vi = get_max(get_vals(curr));
			if(vi != NULL){
				curr->wb_ratio = vi->value;
				curr->best_child = curr->children[vi->index];
			}

		}

	}else{
		cout << "hit max depth. simple eval." << endl;
		cout << "wb is: " << wb << endl;
		if(wb == BLACK){
			Valindex *vi = get_min(get_vals(curr));
			if(vi != NULL){
				curr->wb_ratio = vi->value;
				curr->best_child = curr->children[vi->index];
			}
		}else if(wb == WHITE){
			Valindex *vi = get_max(get_vals(curr));
			if(vi != NULL){
				curr->wb_ratio = vi->value;
				curr->best_child = curr->children[vi->index];
			}
		}
	}
}
