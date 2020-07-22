#include "Generator.h"
#include "Position.h"
#include "Piece.h"
#include <cstdlib>
#include <sys/time.h>

#include <iostream>

using namespace std;


int main(int argc, char**argv){
  if(argc < 2){
    cout << "usage: ./build <int: tree depth>" << endl;
    return -1;
  }
  Position *pstart = new Position(T1);
  Generator G(pstart, BLACK);
  G.build_tree(G.get_tree_root(), 0, BLACK, atoi(argv[1]), false);
  int ncount = G.count_tree_nodes(G.get_tree_root(), 0);
  cout << "Tree has: " << ncount << " nodes!" << endl;

  cout << "--Entering Tree Exploration--" << endl;
 
  Node *root = G.get_tree_root();
  cout << "root has naive eval at: " << root->wb_ratio << " (wb ratio)" << endl;
  int rnc = root->children.size();
  cout << "root node has: " << rnc << " children." << endl;

 
  for(int i=0; i<rnc; i++){
  	Node *ch = root->children[i];
	cout << "--->roots child #" << i << " naive valued at: " << ch->wb_ratio<< endl;
	cout << "--->roots child #" << i << " has: " << ch->children.size() << " 	children" << endl;
  }

  cout << "--Entering Tree Eval--" << endl;
  G.eval_tree(G.get_tree_root(), 0, 3, BLACK, true);
  cout << "root node now valued at: " << root->wb_ratio << endl;
  return 0;
}
