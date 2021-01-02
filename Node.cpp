#include "Node.h"
#include <vector>
using namespace std;


Node::Node() {
	color = WHITE;
	parent = nullptr;
	wb_ratio = 0.0;
	
}

Node::~Node(){
	//delete node_pos; 

}

Node::Node(Node* p, int c, double w, double b) {
	parent = p;
	color = c;
	wb_ratio = w - b;
}

void Node::set_values(double w, double b){
	wb_ratio = w - b;
}

void Node::set_color(int col){
	color = col;
}

void Node::add_child(Node* child){
	children.push_back(child);
}

void Node::set_parent(Node* p) {
	parent = p;
}

void Node::set_board(Board *b){
	node_pos = b;
	board_set = true;
}

bool Node::assign_board_val(Node *parent){
	
	if(board_set){ //board is called node_pos... (stupid!)
		node_pos->calc_final_eval();

		wb_ratio = node_pos->get_wb_ratio();

		return true;
	}else{
		return false;
	}
}
