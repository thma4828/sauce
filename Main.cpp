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

  cout << "--Entering Tree Exploration--" << endl;
 
  Node *root = G.get_tree_root();
  cout << "root has value of: " << root->wb_ratio << " (wb ratio)" << endl;
  int rnc = root->children.size();
  cout << "root node has: " << rnc << " children." << endl;

 /***
  for(int i=0; i<rnc; i++){
 	Node *ch = root->children[i];
	cout << "--->roots child #" << i << " naive valued at: " << ch->wb_ratio<< endl;
	cout << "--->roots child #" << i << " created with move: " << ch->move_string << endl;
	cout << "--->roots child #" << i << " has: " << ch->children.size() << " 	children" << endl;
  }***/

  cout << "Tree evaluation:" << endl;
  G.eval_tree_local(root, 0, BLACK, atoi(argv[2]));
  cout << "root now valued at: " << root->wb_ratio << endl;

  /***
  for(int i=0; i<rnc; i++){
  	Node *ch = root->children[i];
	cout << ch->move_string << " valued at: " << ch->wb_ratio << " (" << i << ")" << endl;
  }***/
  cout << "====line 1 computed (naive) ====" << endl;
  vector<string>line = G.get_line(BLACK);
  int wb_curr = BLACK;
  for(int k=0; k<line.size(); k++){
  	cout << wb_curr << ": " << line[k] << endl;
	wb_curr = !wb_curr;
  }
  cout << "====-------------====" << endl;
  cout << "===line 2 computed (best play) ====" << endl;
  Node *c = root;
  while(c->best_child){
  	c = c->best_child;
	cout << c->move_string << ", " << endl;
  }
  cout << "===--------------====" << endl;
  Node *pxf4 = root->best_child;
  cout << "on node: " << pxf4->move_string << " valued at: " << pxf4->wb_ratio  << " it is now whites move." << endl;
  for(int i=0; i<pxf4->children.size(); i++){
  	Node *child = pxf4->children[i];
	cout << child->move_string<<" valued at: " << child->wb_ratio << endl;
  }
}
