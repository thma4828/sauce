#ifndef GENERATOR_H
#define GENERATOR_H

#include "Board.h"
#include "Position.h"
#include "Tree.h"
#include "Node.h"
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Move.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace std;

class Generator{ //start at a root position and generate a tree
public:
  Generator();
  ~Generator();
  Generator(Position*, int);
  double build_tree(Node*, int, int, int, bool, double, double);
  double build_tree_2(Node*, int, int, int, bool, double, double);
  Node *get_tree_root();
  void del_tree_nodes(Node *);
  void eval_tree(Node*, int, int, int);
  void set_node_count(unsigned int);
  unsigned int get_node_count();

private:
  Tree *move_tree; //tree has to be manually build out of nodes by this class.
  vector<Node*>get_nodes(vector<Move>, Position *, Node *, int);
                                        //p,        //curr  //wb
  void Quicksort(vector<Node*>&, int, int, int); 
  int Partition(vector<Node*>&, int, int, int);
  int node_count; 

};

#endif //GENERATOR_H
