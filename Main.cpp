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
  Position *pstart = new Position(TCHECK);
  Generator G(pstart, BLACK);
  Node *root = G.get_tree_root();
  int alpha = -999; //min value WHITE player assured of getting
  //initially white is only gaurenteed to be checkmated at worst. 
  int beta  = 999; //max value BLACK player assured of getting. 
  G.build_tree(root, 0, BLACK, atoi(argv[1]), false,  alpha, beta);
  unsigned long ncount = G.count_tree_nodes(root, 0);
  cout << "Tree has: " << ncount << " nodes at depth = " << argv[1] << "."  <<  endl;
  int nc  = root->children.size();
  cout << "Root's children moves: (black moves)" << endl;
  for(int j=0; j<nc; j++){
  	cout << "move: " << j << " --> " << root->children[j]->move_string << 
		" || value(+w): " << root->children[j]->wb_ratio << endl;
  }
  cout << "Root position (blacks move) valued at: " << root->wb_ratio << endl;
}
