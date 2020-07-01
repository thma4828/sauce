#ifndef NODE_H
#define NODE_H

using namespace std;
#include <vector>

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
	Node* parent;
	int num_children;
	int color;
	vector<Node*>children;
	float black_value;
	float white_value;
	float wb_ratio;
	Node *best_child;
};
#endif //NODE_H
