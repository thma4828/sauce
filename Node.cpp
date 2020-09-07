#include "Node.h"
#include <vector>
using namespace std;


Node::Node() {
	color = WHITE;
	parent = nullptr;
	black_value = 0.00;
	white_value = 0.00;
	wb_ratio = 0.0;
	kscw = true; //king side castle allowed for white
	kscb = true; //king side castle allowed for black
	qscw = true; //queen side castle allowed for white
	qscb = true; //queen side castle allowed for black. 
	
}

Node::~Node(){
	delete node_pos; 

}

Node::Node(Node* p, int c, float w, float b) {
	parent = p;
	color = c;
	black_value = b;
	white_value = w;
	kscw = true; //king side castle allowed for white
	kscb = true; //king side castle allowed for black
	qscw = true; //queen side castle allowed for white
	qscb = true; //queen side castle allowed for black. 
	wb_ratio = w - b;
}

void Node::set_values(float w, float b){
	black_value = b;
	white_value = w;
	wb_ratio = w - b;
	kscw = true; //king side castle allowed for white
	kscb = true; //king side castle allowed for black
	qscw = true; //queen side castle allowed for white
	qscb = true; //queen side castle allowed for black. 
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
		black_value = node_pos->get_black();
		white_value = node_pos->get_white();
		wb_ratio = white_value - black_value;

		if(parent != NULL){
			kscw = parent->kscw;
			kscb = parent->kscb;
			qscw = parent->qscw;
			qscb = parent->qscb; 
		}
		return true;
	}else{
		return false;
	}
}
