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
  	pstart = new Position(START);
  else if(pos_code == 2)
  	pstart = new Position(TEST_3);
  else if(pos_code == 3)
  	pstart = new Position(TCHECK);
  else if(pos_code == 4)
	  pstart = new Position(TCASTLE); 
  else if (pos_code == 5)
	  pstart = new Position(TPUZZLE1); 
  else
	  pstart = new Position(START); 

  Generator G(pstart, wb);
  Node *root = G.get_tree_root();
  G.set_node_count(1); 
  double alpha = -1000; //min value WHITE player assured of getting
  //initially white is only gaurenteed to be checkmated at worst. 
  double beta  = 1000; //max value BLACK player assured of getting. 
  G.build_tree_2(root, 0, wb, atoi(argv[1]), false,  alpha, beta);
  cout << "Tree has: " << G.get_node_count() << " nodes at depth = " << argv[1] << "."  <<  endl;
  


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
	cout << i << ": " << child->move_string << ": " << child->wb_ratio << endl;
  }


  Node *current = root;
  int i = 1;
  while(current){
  	current = current->best_child;
	if(current){
		cout << i << ": " << current->move_string << ", "; 
		i++;
	}
  } 
  cout << endl;
  return 0; 
}
