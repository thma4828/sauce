#include "Generator.h"
#include "Position.h"
#include "Piece.h"
#include <cstdlib>
#include <sys/time.h>

#include <iostream>

using namespace std;


int main(int argc, char**argv){
  if(argc < 5){
    cout << "usage: ./build <int: tree depth> <int : eval depth> <int : 1 black 0 white> <int: position code>" << endl;
    return -1;
  }
  int wb = atoi(argv[3]);
  int pos_code = atoi(argv[4]);
  Position *pstart;
  if(pos_code == 1)
  	pstart = new Position(T1);
  if(pos_code == 2)
  	pstart = new Position(TEST_3);
  if(pos_code == 3)
  	pstart = new Position(TCHECK);
  if(pos_code == 4)
	  pstart = new Position(TCASTLE); 

  Generator G(pstart, wb);
  Node *root = G.get_tree_root();
  int alpha = -1000; //min value WHITE player assured of getting
  //initially white is only gaurenteed to be checkmated at worst. 
  int beta  = 1000; //max value BLACK player assured of getting. 
  G.build_tree(root, 0, wb, atoi(argv[1]), false,  alpha, beta);
  unsigned long ncount = G.count_tree_nodes(root, 0);
  cout << "Tree has: " << ncount << " nodes at depth = " << argv[1] << "."  <<  endl;
  


  G.eval_tree(root, 0, wb, atoi(argv[2])); 
  cout << "Root eval complete" << endl;

  int nc  = root->children.size();
  cout << "Root has: " << nc << " children" << endl;
  cout << "Root's children moves: ";
  if(wb == BLACK)
	  cout << "blacks move." << endl;
  else
	  cout << "whites move." << endl; 
  for(int i=0; i<nc; i++){
  	Node *child = root->children[i];
	cout << child->move_string << ": " << child->wb_ratio << endl;
  }
  Node *current = root;
  int i = 1;
  while(current->best_child != NULL){
  	current = current->best_child;
	cout << i << ": " << current->move_string << ", "; i++;
  } 
  cout << endl;
  return 0; 
}
