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
  Generator(Position*, int);
  void build_tree(Node*, int, int, int, bool);
  Node *get_tree_root();
  unsigned long count_tree_nodes(Node *, unsigned long);
  void eval_tree(Node*, int, int, int);

private:
  Tree *move_tree; //tree has to be manually build out of nodes by this class.
  vector<Node*>get_nodes(vector<Move>, Position *, Node *, int);
                                        //p,        //curr  //wb

};

#endif //GENERATOR_H
