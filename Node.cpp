#include "Node.h"


Node::Node() {
	color = WHITE;
	parent = nullptr;
	black_value = 0.00;
	white_value = 0.00;
	wb_ratio = 0.0;
}

Node::Node(Node* p, int c, float b, float w) {
	parent = p;
	color = c;
	black_value = b;
	white_value = w;
	wb_ratio = w / b;
}

void Node::set_values(float b, float w){
	black_value = b;
	white_value = w;
	wb_ratio = w / b;
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


