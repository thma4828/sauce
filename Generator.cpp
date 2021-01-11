#include "Generator.h"
#include <stdlib.h>
#include <time.h>


Generator::Generator(){
  srand(time(NULL));
  node_count = 0; 
}

Generator::~Generator(){
    del_tree_nodes(move_tree->root);
}


void Generator::del_tree_nodes(Node *n){
	if(n != NULL){
		if(n->children.size() > 0){
			for(int i=0; i<n->children.size(); i++){
				del_tree_nodes(n->children[i]);
			}
		
		}
		delete n; 
	
	}
}


Generator::Generator(Position *start, int start_color){
  Node *root = new Node(nullptr, start_color, 0.1, 0.1);
  Board *root_board = new Board();
  root_board->set_position(start);
  root_board->set_color(start_color);
  root->set_board(root_board);
  //now node needs to use the board to get
  //the default (naive) evaluation on the position.
  root->assign_board_val(NULL);//node now has naive evaluation.
  move_tree = new Tree(root);
  node_count = 0; 
}

void Generator::eval_tree(Node *n, int depth, int color, int max){
  if(n){
	int c = n->children.size();

	if(depth < (max - 1)){
		//go deeper in tree till bottom level is reached. 
		for(int i=0; i<c; i++){
			Node *ni = n->children[i];
			eval_tree(ni, depth+1, !color, max);
		}
		vector<float>children_values = move_tree->get_vals(n);
		Valindex *v;

		if(color == BLACK){
			v = move_tree->get_min(children_values);
			if(v != NULL){
				n->best_child = n->children[v->index];
				n->wb_ratio = v->value;
			}
		}else if(color == WHITE){
			v = move_tree->get_max(children_values);
			if(v != NULL){
				n->best_child = n->children[v->index];
				n->wb_ratio = v->value;
			}
		}
		return;
	
	}else if(depth == (max - 1)){
		vector<float>children_values = move_tree->get_vals(n);
		Valindex *v;
		
		if(color == BLACK){
			v = move_tree->get_min(children_values);
			if(v != NULL){
				n->best_child = n->children[v->index];
				n->wb_ratio =  v->value;
			}
		}else if(color == WHITE){
			v = move_tree->get_max(children_values);
			if(v != NULL){
				n->best_child = n->children[v->index];
				n->wb_ratio = v->value;
			}
		}
		return;
	
	}else{
		cout << "out of bounds." << endl;
		return;
	}
  }
}

void Generator::set_node_count(unsigned int nc){
	node_count = nc;
}

unsigned int Generator::get_node_count(){
	return node_count; 
}



int Generator::Partition(vector<Node*>&nodes, int p, int r, int wb){
	int nonce = rand() % (r-p) + p; 
	Node *t = nodes[r];
	nodes[r] = nodes[nonce];
	nodes[nonce] = t; 
	
	Node *x = nodes[r];
	int i = p - 1;
	for(int j=p; j<r; j++){
		if(wb == BLACK){
			if(nodes[j]->wb_ratio <=  x->wb_ratio){
				i = i + 1;
				Node *temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
			}
		}else{
			if(nodes[j]->wb_ratio >= x->wb_ratio){
				i = i+1;
				Node *temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp; 
			}
		
		}
	}
	Node *temp = nodes[i+1];
	nodes[i+1] = nodes[r];
	nodes[r] = temp; 
	
	return i+1; 
}

void Generator::Quicksort(vector<Node*>&nodes, int p, int r, int wb){
	if(p < r){
		int q = Partition(nodes, p, r, wb);
		Quicksort(nodes, p, q-1, wb);
		Quicksort(nodes, q+1, r, wb); 
	}

}


vector<Node*> Generator::get_nodes(vector<Move>moves, Position *p, Node *curr, int wb){
  vector<Node*>nodes;
  for(int j=0; j<moves.size(); j++){
    Move m = moves[j];
    //create a node in the tree for position created by this move.
    Node *n1 = new Node(curr, wb, 0.1, 0.1);
    n1->move_string = m.get_move_string();
    Board *b1 = new Board();
    //need a new position same as *p but with move m added
    
    int piece2move = p->the_board[m.x_start][m.y_start];
    int piece_taken = p->the_board[m.x_end][m.y_end];
    Position *pnew = new Position();
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){

          pnew->the_board[x][y] = p->the_board[x][y];

      }
    }
    //TODO: use board cpp to see if move puts enemy king in check. 
    //then add + to the move string if it does! 
    int parent_color = !wb;
    if(parent_color == WHITE && m.is_promote == true){
	    piece2move = WQUEEN; 
	    n1->move_string.push_back('=');
	    n1->move_string.push_back('Q');
    }
    if(parent_color == BLACK && m.is_promote == true){
	    piece2move = BQUEEN;  
	    n1->move_string.push_back('=');
	    n1->move_string.push_back('Q'); 
    }
    pnew->the_board[m.x_start][m.y_start] =  NULLCELL;
    pnew->the_board[m.x_end][m.y_end] = piece2move;
    if(m.is_ep){
    	if(parent_color == WHITE){
		int x_erase = m.x_end + 1; 
		pnew->the_board[x_erase][m.y_end] = NULLCELL; 
	}else if(parent_color == BLACK){
		int x_erase = m.x_end - 1; 
		pnew->the_board[x_erase][m.y_end] = NULLCELL; 
	}
    }
    if(parent_color == BLACK){
    	if(m.is_king_castle){
		pnew->the_board[0][7] = NULLCELL;
		pnew->the_board[0][5] = BROOK;
	}else if(m.is_queen_castle){
		pnew->the_board[0][0] = NULLCELL;
		pnew->the_board[0][3] = BROOK;
	}
    
    }else{
    	if(m.is_king_castle){
		pnew->the_board[7][7] = NULLCELL;
		pnew->the_board[7][5] = WROOK;
		
	}else if(m.is_queen_castle){
		pnew->the_board[7][0] = NULLCELL;
		pnew->the_board[7][3] = WROOK; 
	}
    
    }

    b1->set_position(pnew);
    n1->set_board(b1);
    n1->assign_board_val(curr);
   /** if(parent_color == WHITE){
    	if(n1->node_pos->get_check_black())
		n1->move_string.push_back('+');
    }else{
    	if(n1->node_pos->get_check_white())
		n1->move_string.push_back('+'); 
    }
    ***/
    bool pin = false;
    if(parent_color == WHITE){
    	pin = n1->node_pos->get_check_white(); 
    }else{
    	pin = n1->node_pos->get_check_black(); 
    } 
    if((parent_color == WHITE && curr->node_pos->get_check_white() && 
		    (m.is_king_castle || m.is_queen_castle))
		    ||
		    (parent_color == BLACK && curr->node_pos->get_check_black() && (m.is_king_castle || m.is_queen_castle))){
	//dont push back n1,because you cannot castle out of check.  		    
    }else{    
    	if(!pin)
    		nodes.push_back(n1);
    }
  }
  node_count += nodes.size(); 
  return nodes;
}

bool isPromote(string s){
	bool isp = false;
	for(int i=0; i<s.length(); i++){
		if(s[i] == '='){
			isp = true;
		}
	}
	return isp;
}
bool isCapture(string s){
	bool isc = false;
	for(int i=0; i<s.length(); i++){
		if(s[i] == 'x'){
			isc = true; 
		}
	}
	return isc; 
}
bool isCheck(Node *n, int wb){
	bool isch = false;
	
	if(wb == WHITE){ //node n is result of whites move, 
		isch = n->node_pos->get_check_black();
	}else{
		isch = n->node_pos->get_check_white(); 
	}

	return isch; 
}


vector<Node*> filter_nodes(vector<Node*>nodes, int wb){
	vector<Node*>newNodes;

	for(int i=0; i<nodes.size(); i++){
		Node *n = nodes[i];
	        string s = n->move_string; 
		if(isPromote(s) || isCapture(s) || isCheck(n, wb)){
			newNodes.push_back(n); 
		}else{
			delete n; 
		}
	        	

	}

	return newNodes; 
}

double Generator::build_tree_2(Node* curr, int depth, int wb, int max_depth, bool check, double alpha, double beta)
{
  if(depth <= max_depth){
    
    Position *p = curr->node_pos->get_position();
    vector<Node*>tnodes; 
    
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
        int value = p->the_board[x][y];
        
        if(value != NULLCELL){
        
            if(value == BPAWN || value == WPAWN){ 
              Pawn *pawn;
              if(value == BPAWN && wb == BLACK){ //min player uses beta
                pawn = new Pawn(x, y, BLACK, PAWN, 1, 1);

		if(x != 1){
			pawn->set_been_moved(true);
		}

                pawn->set_pos(p);
                
                vector<Move>pmoves = pawn->set_moves(false);
                vector<Node*>newNodes = get_nodes(pmoves, p, curr, !wb);
		for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
		}

              }else if(value == WPAWN && wb == WHITE){
                pawn = new Pawn(x, y, WHITE, PAWN, 1, 1);
		if(x != 6){
			pawn->set_been_moved(true);
		}
                pawn->set_pos(p);
                
                vector<Move>pmoves = pawn->set_moves(false);
                vector<Node*>newNodes = get_nodes(pmoves, p, curr, !wb);
		for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
		}

        	
	      }

          }else if(value == WKNIGHT || value == BKNIGHT){
            Knight *knight;
            if(value == BKNIGHT && wb == BLACK){
                knight = new Knight(x, y, BLACK, KNIGHT, 2, 3);
                knight->set_pos(p);
                vector<Move>kmoves = knight->set_moves(false);
                vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
		for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
		}
		
            }else if(value == WKNIGHT && wb == WHITE){
              knight = new Knight(x, y, WHITE, KNIGHT, 2, 3);
              knight->set_pos(p);
              vector<Move> kmoves = knight->set_moves(false);
             
              vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
	      for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
	      }

            }
        }else if(value == WBISH || value == BBISH){
		Bishop *bishop;
		if(value == BBISH && wb == BLACK){
			bishop = new Bishop(x, y, BLACK, BISHOP, 1, 1);
			bishop->set_pos(p);
			
			vector<Move>bmoves = bishop->set_moves(false);
			vector<Node*>newNodes = get_nodes(bmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}

			
		}else if(value == WBISH && wb == WHITE){
			bishop = new Bishop(x, y, WHITE, BISHOP, 1, 1);
			bishop->set_pos(p);
		
			vector<Move>bmoves = bishop->set_moves(false);
			vector<Node*>newNodes = get_nodes(bmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}


		}
	}else if(value == WROOK || value == BROOK){
		Rook *rook;
		if(value == WROOK && wb == WHITE){
			rook = new Rook(x, y, WHITE, ROOK, 8, 8);
			rook->set_pos(p);
			vector<Move>rmoves_white = rook->set_moves(false);
			vector<Node*>newNodes = get_nodes(rmoves_white, p, curr, !wb);
			
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}


		}else if(value == BROOK && wb == BLACK){
			rook = new Rook(x, y, BLACK, ROOK, 8, 8);
			rook->set_pos(p);
			vector<Move>rmoves_black = rook->set_moves(false);
			vector<Node*>newNodes = get_nodes(rmoves_black, p, curr, !wb);

			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
		}
	}else if(value == WQUEEN || value == BQUEEN){
		Queen *queen;
		if(value == BQUEEN && wb == BLACK){
			queen = new Queen(x, y, BLACK, QUEEN, 8, 8);
			queen->set_pos(p);
			vector<Move>qmoves = queen->set_moves(false);
			vector<Node*>newNodes = get_nodes(qmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}


		}else if(value == WQUEEN && wb == WHITE){
			queen = new Queen(x, y, WHITE, QUEEN, 8, 8);
			queen->set_pos(p);
			vector<Move>qmoves = queen->set_moves(false);
			vector<Node*>newNodes = get_nodes(qmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}

		}
	
	}else if(value == BKING || value == WKING){
		King *king;
		if(value == BKING && wb == BLACK){
			king = new King(x, y, BLACK, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves(false);
			vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
			
		}else if(value == WKING && wb == WHITE){
			king = new King(x, y, WHITE, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves(false);
			vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
			

		
		}
	} //all pieces added.
	   //nullcell case comes here then returns.  

      }//if(not nullcell ends here)
     
    }	//x
    
    }	//y
    int s = tnodes.size(); 
   
    if(wb == BLACK && check && s == 0){
    	curr->wb_ratio = 999.0;
	return curr->wb_ratio;
    }
    else if(wb == BLACK && check == false && s == 0){
    	curr->wb_ratio = 0.0;
	return curr->wb_ratio;
    }
    else if(wb == WHITE && check && s == 0){
    	curr->wb_ratio = -999.0;
	return curr->wb_ratio;
    }else if(wb == WHITE && check == false && s == 0){
    	curr->wb_ratio = 0.0;
	return curr->wb_ratio; 
    }
    
  bool check_b = false;
  bool check_w = false;
  
  if(depth > 1 && !check){
  	//only explore, checks, promotions, and captures. 
 	tnodes = filter_nodes(tnodes, wb);  
	s = tnodes.size(); 
  }

  
  Quicksort(tnodes, 0, s-1, wb); 
  
  if(wb == WHITE){ //maximizer.
	double value = -1000.0; 
	for(int i=0; i<s; i++){
		Node *n1 = tnodes[i]; 
		curr->add_child(n1); 
		check_b = n1->node_pos->get_check_black();
		if(check_b){
			n1->move_string.push_back('+'); 
		}
		double temp = build_tree(n1, depth+1, !wb, max_depth, check_b, alpha, beta);

		if(temp > value)
			value = temp;

		if(value > alpha)
			alpha = value; 

		if(alpha >= beta){
			for(int n=i+1; n<s; n++){
				delete tnodes[n]; 
			}
			
			break; 
		}
	}
	return value; 

  }else if (wb == BLACK){//minimizer.
	double value = 1000.0; 
	for(int i=0; i<s; i++){
		Node *n1 = tnodes[i];
		curr->add_child(n1); 

		int check_w = n1->node_pos->get_check_white(); 
		if(check_w){
			n1->move_string.push_back('+'); 
		}
		double temp = build_tree(n1, depth+1, !wb, max_depth, check_w, alpha, beta); 
		if(temp < value)
			value = temp;

		if(value < beta)
			beta = value;

		if(beta <= alpha){
			for(int n=i+1; n<s; n++)
				delete tnodes[n]; 
			break;
		}
	}
	return value; 

  }

 }
	return curr->wb_ratio; 

}


double Generator::build_tree(Node *curr, int depth, int wb, int max_depth, bool check, double alpha, double beta)
{
  if(depth <= max_depth){
    
    Position *p = curr->node_pos->get_position();
    vector<Node*>tnodes; 
    
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
        int value = p->the_board[x][y];
        
        if(value != NULLCELL){
        
            if(value == BPAWN || value == WPAWN){ 
              Pawn *pawn;
              if(value == BPAWN && wb == BLACK){ //min player uses beta
                pawn = new Pawn(x, y, BLACK, PAWN, 1, 1);

		if(x != 1){
			pawn->set_been_moved(true);
		}

                pawn->set_pos(p);
                
                vector<Move>pmoves = pawn->set_moves(false);
                vector<Node*>newNodes = get_nodes(pmoves, p, curr, !wb);
		for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
		}

              }else if(value == WPAWN && wb == WHITE){
                pawn = new Pawn(x, y, WHITE, PAWN, 1, 1);
		if(x != 6){
			pawn->set_been_moved(true);
		}
                pawn->set_pos(p);
                
                //cout << "in generator: pawn has set moves." << endl;
                vector<Move>pmoves = pawn->set_moves(false);
                vector<Node*>newNodes = get_nodes(pmoves, p, curr, !wb);
                //cout << "in generator: new nodes created." << endl;
		for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
		}

        	
	      }

          }else if(value == WKNIGHT || value == BKNIGHT){
            //cout << "in generator: knight" << endl;
            Knight *knight;
            if(value == BKNIGHT && wb == BLACK){
                knight = new Knight(x, y, BLACK, KNIGHT, 2, 3);
                knight->set_pos(p);
                vector<Move>kmoves = knight->set_moves(false);
                vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
		for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
		}
		
            }else if(value == WKNIGHT && wb == WHITE){
              knight = new Knight(x, y, WHITE, KNIGHT, 2, 3);
              knight->set_pos(p);
              vector<Move> kmoves = knight->set_moves(false);
             
              vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
	      for(int j=0; j<newNodes.size(); j++){
			tnodes.push_back(newNodes[j]); 
	      }

            }
            //TODO BELOW + all other piece types.
        }else if(value == WBISH || value == BBISH){
//		cout << "in generator: in bishop." << endl;
		Bishop *bishop;
		if(value == BBISH && wb == BLACK){
		//	cout << "in generator: in bishop: black bishop setting pos and moves" << endl;
			bishop = new Bishop(x, y, BLACK, BISHOP, 1, 1);
			bishop->set_pos(p);
			
			vector<Move>bmoves = bishop->set_moves(false);
			vector<Node*>newNodes = get_nodes(bmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}

			
		}else if(value == WBISH && wb == WHITE){
		//	cout << "in generator: in bishop: white bishop setting pos and moves." << endl;
			bishop = new Bishop(x, y, WHITE, BISHOP, 1, 1);
			bishop->set_pos(p);
		
			vector<Move>bmoves = bishop->set_moves(false);
			vector<Node*>newNodes = get_nodes(bmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}


		}
	}else if(value == WROOK || value == BROOK){
		//cout << "in generator: rook" << endl;
		Rook *rook;
		if(value == WROOK && wb == WHITE){
			rook = new Rook(x, y, WHITE, ROOK, 8, 8);
			rook->set_pos(p);
			vector<Move>rmoves_white = rook->set_moves(false);
			vector<Node*>newNodes = get_nodes(rmoves_white, p, curr, !wb);
			
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}


		}else if(value == BROOK && wb == BLACK){
			rook = new Rook(x, y, BLACK, ROOK, 8, 8);
			rook->set_pos(p);
			vector<Move>rmoves_black = rook->set_moves(false);
			vector<Node*>newNodes = get_nodes(rmoves_black, p, curr, !wb);

			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
		}
	}else if(value == WQUEEN || value == BQUEEN){
		//cout << "in generator: queen" << endl;
		Queen *queen;
		if(value == BQUEEN && wb == BLACK){
			queen = new Queen(x, y, BLACK, QUEEN, 8, 8);
			queen->set_pos(p);
			vector<Move>qmoves = queen->set_moves(false);
			vector<Node*>newNodes = get_nodes(qmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}


		}else if(value == WQUEEN && wb == WHITE){
			queen = new Queen(x, y, WHITE, QUEEN, 8, 8);
			queen->set_pos(p);
			vector<Move>qmoves = queen->set_moves(false);
			vector<Node*>newNodes = get_nodes(qmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}

		}
	
	}else if(value == BKING || value == WKING){
		King *king;
		if(value == BKING && wb == BLACK){
			king = new King(x, y, BLACK, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves(false);
			vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
			
		}else if(value == WKING && wb == WHITE){
			king = new King(x, y, WHITE, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves(false);
			vector<Node*>newNodes = get_nodes(kmoves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
			

		
		}
	} //all pieces added.
	   //nullcell case comes here then returns.  

      }//if(not nullcell ends here)
     
    }	//x
    
    }	//y
    int s = tnodes.size(); 
   
    if(wb == BLACK && check && s == 0){
    	curr->wb_ratio = 999.0;
	return curr->wb_ratio;
    }
    else if(wb == BLACK && check == false && s == 0){
    	curr->wb_ratio = 0.0;
	return curr->wb_ratio;
    }
    else if(wb == WHITE && check && s == 0){
    	curr->wb_ratio = -999.0;
	return curr->wb_ratio;
    }else if(wb == WHITE && check == false && s == 0){
    	curr->wb_ratio = 0.0;
	return curr->wb_ratio; 
    }
    
  Quicksort(tnodes, 0, s-1, wb); 
  bool check_b = false;
  bool check_w = false;
  if(depth > 0 && s > 8 && s < 20){
  	int snew = s >> 1; 
	for(int si = snew; si<s; si++){
		delete tnodes[si];
	}
	tnodes.resize(snew);
	s = snew; 
  }else if(depth > 0 && s >= 20){
  	int snew = s >> 2;
	for(int si=snew; si<s; si++){
		delete tnodes[si]; 
	}
	tnodes.resize(snew);
        s = snew; 	
  } 
  if(wb == WHITE){ //maximizer.
	double value = -1000.0; 
	for(int i=0; i<s; i++){
		Node *n1 = tnodes[i]; 
		curr->add_child(n1); 
		check_b = n1->node_pos->get_check_black();
		if(check_b){
			n1->move_string.push_back('+');
		}
		double temp = build_tree(n1, depth+1, !wb, max_depth, check_b, alpha, beta);

		if(temp > value)
			value = temp;

		if(value > alpha)
			alpha = value; 

		if(alpha >= beta){
			for(int n=i+1; n<s; n++){
				delete tnodes[n]; 
			}
			
			break; 
		}
	}
	return value; 

  }else if (wb == BLACK){//minimizer.
	double value = 1000.0; 
	for(int i=0; i<s; i++){
		Node *n1 = tnodes[i];
		curr->add_child(n1); 

		int check_w = n1->node_pos->get_check_white(); 
		if(check_w){
			n1->move_string.push_back('+'); 
		}
		double temp = build_tree(n1, depth+1, !wb, max_depth, check_w, alpha, beta); 
		if(temp < value)
			value = temp;

		if(value < beta)
			beta = value;

		if(beta <= alpha){
			for(int n=i+1; n<s; n++)
				delete tnodes[n]; 
			break;
		}
	}
	return value; 

  }

 }
	return curr->wb_ratio; 

}

Node *Generator::get_tree_root(){
  return move_tree->root;
}
