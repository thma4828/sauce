
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

