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
  Node *root = G.get_tree_root();
  G.build_tree(root, 0, BLACK, atoi(argv[1]), false);
  unsigned long ncount = G.count_tree_nodes(root, 0);
  cout << "Tree has: " << ncount << " nodes at depth = " << argv[1] << "."  <<  endl;
  int nc  = root->children.size();
  cout << "Root's children moves: (black moves)" << endl;
  for(int j=0; j<nc; j++){
  	cout << "move: " << j << " --> " << root->children[j]->move_string << 
		" || value(+w): " << root->children[j]->wb_ratio << endl;
  }
  cout << "Root position (blacks move) valued at: " << root->wb_ratio << endl;
  G.eval_tree(root, 0, BLACK, atoi(argv[2])); 
  cout << "after eval position valued at: " << root->wb_ratio << endl; 
  
  cout << "line calculated: " << endl;
  Node *current = root;
  current = current->best_child;
  while(current != NULL){
	cout << "(" << current->move_string << " , " << current->wb_ratio << ")" << endl;
	current = current->best_child;

  }
}
