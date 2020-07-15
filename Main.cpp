#include "Generator.h"
#include "Position.h"
#include "Piece.h"

#include <iostream>

using namespace std;


int main(){
  Position *pstart = new Position(T1);
  Generator G(pstart, BLACK);
  G.build_tree(G.get_tree_root(), 0, BLACK, 1, false);
  return 0;
}
