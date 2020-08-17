#ifndef NODE_H
#define NODE_H
#include "Position.h"
#include "Board.h"

using namespace std;
#include <vector>
#include <string>


#define BLACK 1
#define WHITE 0

class Node
{
public:
	Node();

	Node(Node*, int, float, float);

	void set_values(float, float);
	void set_color(int);
	void add_child(Node*);
	void set_parent(Node*);
	void set_board(Board*);

	bool assign_board_val();

	Node* parent;
	int num_children;
	int color;
	vector<Node*>children;
	float black_value;
	float white_value;
	float wb_ratio;
	Node *best_child;

	Board *node_pos;
	bool board_set;
	int MCTS_visits; 	
	string move_string;

};
#endif //NODE_H
