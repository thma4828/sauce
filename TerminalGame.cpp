#include "Generator.h"
#include "Position.h"
#include "Piece.h"

#include <iostream>

using namespace std;

int main(int argc, char**argv){
	Position *p = new Position(START); 
	
	int wb = WHITE;

	Generator *G = new Generator(p, wb); 
	Node *root;
	
	double alpha = -1000;
	double beta = 1000; 
	
	int turn = 1;
	string move;
	cout << "new chess game: you play as white." << endl;
	while(true){
		cout << "turn :" << turn << endl;
	        cout << "turn wb: " << wb << endl;	
		alpha = -1000;
		beta = 1000;
		root = G->get_tree_root(); 
		G->build_tree(root, 0, wb, 2,root->node_pos->get_check_white(), alpha, beta); 
		cout << "your possible moves are: " << endl;

		int rc = root->children.size(); 
		for(int i=0; i<rc; i++){
			cout << root->children[i]->move_string << endl;
		}
		
		cout << "enter your move: " << endl;
		getline(cin, move); 

		Node *move_node = NULL; 
		bool move_found = false; 

		for(int i=0; i<root->children.size(); i++){
			Node *temp = root->children[i];

			if(temp->move_string == move){
				move_node = temp; 
				move_found = true;
				wb = !wb; 
				break;
			}
		}
		if(move_found){
			
			turn++;
			Position *pn = move_node->node_pos->get_position();
		        
			delete G;  
			Generator *P = new Generator(pn, wb);
			root = P->get_tree_root(); 
			alpha = -1000;
			beta = 1000;

			P->build_tree(root, 0, wb, 3, root->node_pos->get_check_black(), alpha, beta);
			P->eval_tree(root, 0, wb, 4); 
			
			Node *m = root->best_child; 
			cout << "computer makes the move: "
			       	<< m->move_string << 
				" valued at: " << m->wb_ratio << endl; 	

			Position *np = m->node_pos->get_position(); 

			delete P; 

			G = new Generator(np, !wb);
				
			wb = !wb; 
		}else{
		  cout << "move does not exist: try again." << endl;

		} 
	}

}
