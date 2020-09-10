#include "Generator.h"


Generator::Generator(){
  //
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




unsigned long Generator::count_tree_nodes(Node *n, unsigned long c){
	c = c + 1;
	for(int j=0; j<n->children.size(); j++){
		Node *child = n->children[j];
		c = count_tree_nodes(child, c);
	}
	return c;
}

int Generator::Partition(vector<Node*>&nodes, int p, int r, int wb){
	
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

    bool pin = false;
    if(parent_color == WHITE){
    	pin = n1->node_pos->get_check_white(); 

    }else{
    	pin = n1->node_pos->get_check_black(); 
    } 
    
    if(!pin && n1->color == wb)
    	nodes.push_back(n1);
  }
  return nodes;
}
//TODO add if() before adding nodes to check if piece was pinned (if moving it puts their own king into check.
float Generator::build_tree(Node *curr, int depth, int wb, int max_depth, bool check, float alpha, float beta)
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
    	curr->wb_ratio = 999;
	return curr->wb_ratio;
    }
    else if(wb == BLACK && check == false && s == 0){
    	curr->wb_ratio = 0;
	return curr->wb_ratio;
    }
    else if(wb == WHITE && check && s == 0){
    	curr->wb_ratio = -999;
	return curr->wb_ratio;
    }else if(wb == WHITE && check == false && s == 0){
    	curr->wb_ratio = 0;
	return curr->wb_ratio; 
    }
    
    Quicksort(tnodes, 0, s-1, wb); 
  if(wb == BLACK){ //only nodes where white moves such that white not (still) in check should show. 
		float value = 1000;
		float beta_hat;
		bool check_white;
		bool check_black;
                for(int k=0; k < s; k++){
                  Node *n1 = tnodes[k];
                  curr->add_child(n1);
                  
                  check_white = n1->node_pos->get_check_white();
                  
                  check_black = n1->node_pos->get_check_black();

		  if(check_white)
			  n1->move_string.push_back('+'); 

                  if(depth+1 <= max_depth){
                     beta_hat = build_tree(n1, depth+1, !wb, max_depth, check_white, alpha, beta);
		     if(beta_hat < value){
		     	value  = beta_hat; 
		     }
		     if(value < beta){
		     	beta = value;
		     }
		     if(beta <= alpha){
		     	     int j = k+1;
			     for(j; j<s; j++){
			     	Node *nj = tnodes[j];
				delete nj; 
			     }
			     break; 
		     }
		  }
                }
		return value; 
  	
  
  }else{
		float value = -1000;
		float alpha_hat;
                for(int k=0; k<s; k++){
                  Node *n1 = tnodes[k];
                  curr->add_child(n1);
		  bool check_white;
		  bool check_black;
                  
                  check_white = n1->node_pos->get_check_white();
                  
                  check_black = n1->node_pos->get_check_black();

		  if(check_black)
			  n1->move_string.push_back('+');

                  if(depth+1 <= max_depth){
                    alpha_hat = build_tree(n1, depth+1, !wb, max_depth, check_black, alpha, beta);
		    if(alpha_hat > value){
		    	value = alpha_hat;
		    }
		    if(value  > alpha){
		    	alpha = value;
		    }
		    if(alpha >= beta){

		     	     int j = k+1;
			     for(j; j<s; j++){
			     	Node *nj = tnodes[j];
				delete nj; 
			     }
		    	break;
		    }
		  }
                }
		return value;
  	
  
  
  }

  }else{
  	cout << "depth reached."<< endl;
	return curr->wb_ratio; 
  }

}

Node *Generator::get_tree_root(){
  return move_tree->root;
}
