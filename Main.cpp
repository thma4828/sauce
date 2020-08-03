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

  cout << "Root position (blacks move) valued at: " << root->wb_ratio << endl;
  int rnc = root->children.size();
  for(int j=0; j<rnc; j++){
  	cout << "Root's child #" << j << " is move: " << root->children[j]->move_string << " and valued at: " << root->children[j]->wb_ratio << endl; 
  }
  Node *qxc3 = root->children[20];
  cout << "black makes move Qxc3, which has children #'d" << endl;
  int qnc = qxc3->children.size();
  for(int i=0; i<qnc; i++){
  	cout << i << ": " << qxc3->children[i]->move_string << " valued at: " << qxc3->children[i]->wb_ratio << endl; 
  }
}
