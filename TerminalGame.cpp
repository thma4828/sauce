#include "Generator.h"
#include "Position.h"
#include "Piece.h"

#include <iostream>

using namespace std;

int main(int argc, char**argv){
	Position *p = new Position(START); 
	
	int wb = WHITE;

	Generator G = Generator(p, wb); 
	Node *root = G.get_tree_root(); 
	int alpha = -1000;
	int beta = 1000; 
	
	int turn = 1;
	string move;
	cout << "new chess game: you play as white." << endl;
	while(turn < 10){
		G.build_tree(G.get_tree_root(), 0, wb, 2, false, alpha, beta); 
		cout << "enter your move: " << endl;
		getline(cin, move); 

		Node *move_node = NULL; 
		bool move_found = false; 
		for(int i=0; i<root->children.size(); i++){
			Node *temp = root->children[i];

			if(temp->move_string == move){
				move_node = temp;
				move_found = true;
				break;
			}
		}
		if(move_found){
			turn++;
			Position *pn = move_node->node_pos->get_position();
		        
			wb = !wb; 
			G = Generator(pn, wb);
			bool c;
			if(wb == WHITE)
				c = move_node->node_pos->
					get_check_black();
			else
				c = move_node->
					node_pos->get_check_white(); 
			G.build_tree(G.get_tree_root(),
				       	0, wb, 4, c, alpha, beta);
			G.eval_tree(root, 0, wb, 3); 

			cout << "computer makes the move: "
			       	<< root->move_string << endl; 
		        wb = !wb; 	
			root = root->best_child;

			
			G = Generator(root->node_pos->get_position(), wb); 
				
		}else{
		  cout << "move does not exist: try again." << endl;

		}

	}

}
