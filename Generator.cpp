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
  root->assign_board_val();//node now has naive evaluation.
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
			n->best_child = n->children[v->index];
			n->wb_ratio = v->value;
		}else if(color == WHITE){
			v = move_tree->get_max(children_values);
			n->best_child = n->children[v->index];
			n->wb_ratio = v->value;
		}
		return;
	
	}else if(depth == (max - 1)){
		vector<float>children_values = move_tree->get_vals(n);
		Valindex *v;
		
		if(color == BLACK){
			v = move_tree->get_min(children_values);
			n->best_child = n->children[v->index];
			n->wb_ratio =  v->value;
		}else if(color == WHITE){
			v = move_tree->get_max(children_values);
			n->best_child = n->children[v->index];
			n->wb_ratio = v->value;
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
    b1->set_position(pnew);
    n1->set_board(b1);
    n1->assign_board_val();

    
    bool pin = false;
    if(parent_color == WHITE){
    	pin = n1->node_pos->get_check_white(); 

    }else{
    	pin = n1->node_pos->get_check_black(); 
    } 
    
    if(!pin)
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
    if(!check){
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
        int value = p->the_board[x][y];
        
        if(value != NULLCELL){
        
            if(value == BPAWN || value == WPAWN){ 
              Pawn *pawn;
              if(value == BPAWN && wb == BLACK){ //min player uses beta
                pawn = new Pawn(x, y, BLACK, PAWN, 1, 1);

		if(x > 1){
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
		if(x < 6){
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
		//king case, kings not in check. 
		King *king;
		if(value == BKING && wb == BLACK){
			king = new King(x, y, BLACK, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves(false);
			vector<Move>valid_moves;
			curr->node_pos->get_check_black();
			vector<Square>white_threats = curr->node_pos->get_threat_squares(wb); 
			for(int i=0; i<kmoves.size(); i++){
				Move mi = kmoves[i];
				bool valid = true;
				for(int j=0; j<white_threats.size(); j++){
					Square wt = white_threats[j];
					//king cannot move into check. 
					if(wt.x == mi.x_end && wt.y == mi.y_end){
						valid = false;
					}
				}
				if(valid)
					valid_moves.push_back(mi); 
			}
			vector<Node*>newNodes = get_nodes(valid_moves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
			
		}else if(value == WKING && wb == WHITE){
			king = new King(x, y, WHITE, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves(false);
			vector<Move>valid_moves;
			curr->node_pos->get_check_white(); 
			vector<Square>black_threats = curr->node_pos->get_threat_squares(wb); 

			for(int i=0; i<kmoves.size(); i++){
				Move mi = kmoves[i];
				bool valid = true;
				for(int j=0; j<black_threats.size(); j++){
					Square bt = black_threats[j];
					if(bt.x == mi.x_end && bt.y ==  mi.y_end){
						valid = false;
					}
				}
				if(valid)
					valid_moves.push_back(mi);
			}
			vector<Node*>newNodes = get_nodes(valid_moves, p, curr, !wb);
			for(int j=0; j<newNodes.size(); j++){
				tnodes.push_back(newNodes[j]); 
			}
			

		
		}
	} //all pieces added.
	   //nullcell case comes here then returns.  

      }//if(not nullcell ends here)
     
    }	//x
    
    }	//y

    }else{ //check on the board.
                  //if no king moves there may be a blocking move to stop checkmate...
                  //if wb == WHITE && is_check then there is a check on the white king. (makes sense)
		  //
		  
		  int kx, ky;
		  if(wb == WHITE){
		  	for(int i=0; i<8; i++){
		  		for(int j=0; j<8; j++){
					if(p->the_board[i][j] == WKING){
						kx = i;
						ky = j;
					}
				}
		  	}
		  	King *king = new King(kx, ky, WHITE, KING, 1, 1); 
		  	king->set_pos(p); 

		  
		  	curr->node_pos->get_check_white(); 
			vector<Square>black_threats = curr->node_pos->get_threat_squares(wb);

			vector<Move>moves = king->set_moves(false); 

			vector<Move>valid_moves;

			for(int i=0; i<moves.size(); i++){
				Move m = moves[i];
				bool valid = true;
				for(int j=0; j<black_threats.size(); j++){
					Square threat = black_threats[j];

					if(threat.x == m.x_end && threat.y == m.y_end){
						valid = false;
					}
				}
				if(valid)
					valid_moves.push_back(m);
			}
			//if there are no valid moves,
			//we must search the position for a friendly piece with which
			//we can block the check
			//then if this doesn't exist it is mate. 
			tnodes = get_nodes(valid_moves, p, curr, !wb);
		
		

		  }else{ //wb == BLACK
			for(int x=0; x<8; x++){
				for(int y=0; y<8; y++){
					if(p->the_board[x][y] == BKING){
						kx = x;
						ky = y;
					}
				}
			}
			King *king = new King(kx, ky, BLACK, KING, 1, 1);
			king->set_pos(p);

			curr->node_pos->get_check_black();
			vector<Square>white_threats = curr->node_pos->get_threat_squares(wb);

			vector<Move>moves = king->set_moves(false);
			
			vector<Move>valid_moves;
			for(int i=0; i<moves.size(); i++){
				Move mi = moves[i];
				bool valid = true;
				for(int j=0; j<white_threats.size(); j++){
					Square sj = white_threats[j];
					if(sj.x == mi.x_end && sj.y == mi.y_end){
						valid = false;
					}
				}
				if(valid)
					valid_moves.push_back(mi);
			}
			tnodes = get_nodes(valid_moves, p, curr, !wb);

			

		  
		  }

    }

  if(wb == BLACK){
		float value = 999;
		float beta_hat;
                for(int k=0; k<tnodes.size(); k++){
                  Node *n1 = tnodes[k];
                  curr->add_child(n1);
                  if(wb == BLACK)
                    check = n1->node_pos->get_check_white();
                  else
                    check = n1->node_pos->get_check_black();

                  if(depth+1 <= max_depth){
                     beta_hat = build_tree(n1, depth+1, !wb, max_depth, check, alpha, beta);
		     if(beta_hat < value){
		     	value  = beta_hat; 
		     }
		     if(beta < value){
		     	beta = value;
		     }
		     if(beta <= alpha){
		     	break; 
		     }
		  }
                }
		return value; 
  	
  
  }else{
		float value = -999;
		float alpha_hat;
                for(int k=0; k<tnodes.size(); k++){
                  Node *n1 = tnodes[k];
                  curr->add_child(n1);
                  if(wb == BLACK)
                    check = n1->node_pos->get_check_white();
                  else
                    check = n1->node_pos->get_check_black();

                  if(depth+1 <= max_depth){
                    alpha_hat = build_tree(n1, depth+1, !wb, max_depth, check, alpha, beta);
		    if(alpha_hat > value){
		    	value = alpha_hat;
		    }
		    if(value  > alpha){
		    	alpha = value;
		    }
		    if(alpha >= beta){
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
