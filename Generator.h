#ifndef GENERATOR_H
#define GENERATOR_H

#include "Board.h"
#include "Position.h"
#include "Tree.h"
#include "Node.h"
#include "Piece.h"

using namespace std;

class Generator{ //start at a root position and generate a tree
public:
  Generator();
  Generator(Position*, int);

private:
  Tree *move_tree; //tree has to be manually build out of nodes by this class.



};

#endif //GENERATOR_H
