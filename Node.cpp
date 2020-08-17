#include "Node.h"
#include <vector>
using namespace std;


Node::Node() {
	color = WHITE;
	parent = nullptr;
	black_value = 0.00;
	white_value = 0.00;
	wb_ratio = 0.0;
	MCTS_visits = 0;
}

Node::Node(Node* p, int c, float w, float b) {
	parent = p;
	color = c;
	black_value = b;
	white_value = w;
	wb_ratio = w - b;
	MCTS_visits = 0; 
}

void Node::set_values(float w, float b){
	black_value = b;
	white_value = w;
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

bool Node::assign_board_val(){
	if(board_set){ //board is called node_pos... (stupid!)
		node_pos->calc_final_eval();
		black_value = node_pos->get_black();
		white_value = node_pos->get_white();
		wb_ratio = white_value - black_value;
		return true;
	}else{
		return false;
	}
}
