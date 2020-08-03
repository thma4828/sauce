#include "Generator.h"
#include "Position.h"
#include "Piece.h"
#include <cstdlib>
#include <sys/time.h>

#include <iostream>

using namespace std;


int main(int argc, char**argv){
  if(argc < 3){
    cout << "usage: ./build <int: tree depth> <int : eval depth>" << endl;
    return -1;
  }
  Position *pstart = new Position(T1);
  Generator G(pstart, BLACK);
  G.build_tree(G.get_tree_root(), 0, BLACK, atoi(argv[1]), false);
  unsigned long ncount = G.count_tree_nodes(G.get_tree_root(), 0);
  cout << "Tree has: " << ncount << " nodes!" << endl;
}
