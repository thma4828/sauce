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
  cout << "in generator: get_nodes(): entering routine." << endl;
  for(int j=0; j<moves.size(); j++){
    cout << "in generator: get_nodes(): for loop iter: " << j << endl;
    Move m = moves[j];
    //create a node in the tree for position created by this move.
    Node *n1 = new Node(curr, wb, 0.1, 0.1);
    n1->move_string = m.get_move_string();
    cout << "------>iter " << j << ": move " << n1->move_string << " on the board." << endl;
    Board *b1 = new Board();
    //need a new position same as *p but with move m added
    cout << "------>iter " << j << ": node and board initialized in memory" << endl;
    cout << "------>iter " << j << ": move has x_start, y_start = (" <<
    m.x_start << "," << m.y_start << ")"<<endl;
    cout << "------>iter " << j << ": move has x_end, y_end = (" <<
    m.x_end << "," << m.y_end << ")"<<endl;
    if(m.is_take){
    	cout << "------>iter " << j << ": " << m.piece_type <<" takes enemy piece." << endl;
    }
    
    int piece2move = p->the_board[m.x_start][m.y_start];
    int piece_taken = p->the_board[m.x_end][m.y_end];
    cout << "------>iter " << j << ": Piece to move is of code: " << piece2move << endl;
    if(m.is_take){
    	cout << "------>iter " << j << ": Piece taken is of code: " << piece_taken << endl;
    }
    Position *pnew = new Position();
    cout << "------>iter " << j << ": going into 8x8 double for loop to copy most of position over." << endl;
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){

          pnew->the_board[x][y] = p->the_board[x][y];

      }
    }
    //TODO: use board cpp to see if move puts enemy king in check. 
    //then add + to the move string if it does! 
    cout << "------>iter " << j << ": old position copied over." << endl;
    pnew->the_board[m.x_start][m.y_start] =  NULLCELL;
    pnew->the_board[m.x_end][m.y_end] = piece2move;
    cout << "------>iter " << j << ": new position made." << endl;
    b1->set_position(pnew);
    n1->set_board(b1);
    n1->assign_board_val();

    nodes.push_back(n1);
  }
  return nodes;
}

void Generator::build_tree(Node *curr, int depth, int wb, int max_depth, bool check){
  cout << "in generator: build_tree(): at depth: " << depth << " / " << max_depth << endl;
  if(depth <= max_depth){
    if(depth > 0){
    	cout << "in generator: entering node created with move: " << curr->move_string << endl;
    }
    Position *p = curr->node_pos->get_position();
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){
        cout << "in generator: build_tree(): at depth: " << depth << " / " << max_depth << endl;
        int value = p->the_board[x][y];
        cout << "--->with value of" << value << endl;
        if(value != NULLCELL){
          if(!check){
            if(value == BPAWN || value == WPAWN){
              Pawn *pawn;
              if(value == BPAWN && wb == BLACK){
                pawn = new Pawn(x, y, BLACK, PAWN, 1, 1);

		if(x > 1){
			pawn->set_been_moved(true);
		}

                pawn->set_pos(p);
                pawn->set_moves();
                cout << "in generator: pawn has set moves." << endl;
                vector<Move>pmoves = pawn->get_moves();
                vector<Node*>tnodes = get_nodes(pmoves, p, curr, !wb);
                cout << "in generator: new nodes created." << endl;
                for(int k=0; k<tnodes.size(); k++){
                  Node *n1 = tnodes[k];
                  curr->add_child(n1);
                  if(wb == BLACK)
                    check = n1->node_pos->get_check_white();
                  else
                    check = n1->node_pos->get_check_black();

                  //node should be added with correct parent and naive wb_eval value.
                  if(depth+1 <= max_depth)
                    build_tree(n1, depth+1, !wb, max_depth, check);
                }
              }else if(value == WPAWN && wb == WHITE){
                pawn = new Pawn(x, y, WHITE, PAWN, 1, 1);
		if(x < 6){
			pawn->set_been_moved(true);
		}
                pawn->set_pos(p);
                pawn->set_moves();
                cout << "in generator: pawn has set moves." << endl;
                vector<Move>pmoves = pawn->get_moves();
                vector<Node*>tnodes = get_nodes(pmoves, p, curr, !wb);
                cout << "in generator: new nodes created." << endl;
                for(int k=0; k<tnodes.size(); k++){
                  Node *n1 = tnodes[k];
                  curr->add_child(n1);
                  if(wb == BLACK)
                    check = n1->node_pos->get_check_white();
                  else
                    check = n1->node_pos->get_check_black();

                  //node should be added with correct parent and naive wb_eval value.
                  if(depth+1 <= max_depth)
                    build_tree(n1, depth+1, !wb, max_depth, check);
                }

              }else{
                //
              }
                //




                  //rbuild the tree like depth-first-search to max_depth.


          }else if(value == WKNIGHT || value == BKNIGHT){
            cout << "in generator: knight" << endl;
            Knight *knight;
            if(value == BKNIGHT && wb == BLACK){
                knight = new Knight(x, y, BLACK, KNIGHT, 2, 3);
                knight->set_pos(p);
                vector<Move>kmoves = knight->set_moves();
		if(kmoves.size() < 1)
			cout << "in generator: knight, black knight has no moves" << endl;
                vector<Node*>tnodes = get_nodes(kmoves, p, curr, !wb);
                for(int t=0; t<tnodes.size(); t++){
                  Node *n1 = tnodes[t];
                  curr->add_child(n1);
                  if(wb == BLACK)
                    check = n1->node_pos->get_check_white();
                  else
                    check = n1->node_pos->get_check_black();

                  //node should be added with correct parent and naive wb_eval value.
                  if(depth+1 <= max_depth)
                    build_tree(n1, depth+1, !wb, max_depth, check);


                }

            }else if(value == WKNIGHT && wb == WHITE){
              knight = new Knight(x, y, WHITE, KNIGHT, 2, 3);
              knight->set_pos(p);
              vector<Move> kmoves = knight->set_moves();
             // kmoves = knight->get_moves()
	      if(kmoves.size() < 1)
		      cout << "in generator: knight: white night has no moves." << endl;
              vector<Node*>tnodes = get_nodes(kmoves, p, curr, !wb);

              for(int t=0; t<tnodes.size(); t++){
                Node *n1 = tnodes[t];
                curr->add_child(n1);
                if(wb == BLACK)
                  check = n1->node_pos->get_check_white();
                else
                  check = n1->node_pos->get_check_black();

                //node should be added with correct parent and naive wb_eval value.
                if(depth+1 <= max_depth)
                  build_tree(n1, depth+1, !wb, max_depth, check);

              }


            }
            //TODO BELOW + all other piece types.
        }else if(value == WBISH || value == BBISH){
		cout << "in generator: in bishop." << endl;
		Bishop *bishop;
		if(value == BBISH && wb == BLACK){
			cout << "in generator: in bishop: black bishop setting pos and moves" << endl;
			bishop = new Bishop(x, y, BLACK, BISHOP, 1, 1);
			bishop->set_pos(p);
			bishop->set_moves();
			vector<Move>bmoves = bishop->get_moves();
			if(bmoves.size() < 1){
				cout << "in generator: bishop: bishop has no moves." << endl;
			}
			vector<Node *>tnodes = get_nodes(bmoves, p, curr, !wb);
			
			for(int t=0; t<tnodes.size(); t++){
				Node *n1 = tnodes[t];
				curr->add_child(n1);

				check = n1->node_pos->get_check_white();

				if(depth+1 <= max_depth){ 
					build_tree(n1, depth+1, !wb, max_depth, check);
				}
			}
	
		}else if(value == WBISH && wb == WHITE){
			cout << "in generator: in bishop: white bishop setting pos and moves." << endl;
			bishop = new Bishop(x, y, WHITE, BISHOP, 1, 1);
			bishop->set_pos(p);
		//	bishop->set_moves();
			vector<Move>bmoves = bishop->set_moves();
			vector<Node*>tnodes = get_nodes(bmoves, p, curr, !wb);
			if(bmoves.size() < 1){
				cout << "in generator: bishop: (white) bishop has no moves." << endl;
			}
			for(int t=0; t<tnodes.size(); t++){
				Node *n1 = tnodes[t];
				curr->add_child(n1);

				check = n1->node_pos->get_check_black();

				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);
				}
			}
		}
	}else if(value == WROOK || value == BROOK){
		cout << "in generator: rook" << endl;
		Rook *rook;
		if(value == WROOK && wb == WHITE){
			rook = new Rook(x, y, WHITE, ROOK, 8, 8);
			rook->set_pos(p);
			vector<Move>rmoves_white = rook->set_moves();
			vector<Node*>rnodes = get_nodes(rmoves_white, p, curr, !wb);
			if(rnodes.size() < 1)
				cout << "in generator: rook has no moves." << endl;

			for(int t=0; t<rnodes.size(); t++){
				Node *n1 = rnodes[t];
				curr->add_child(n1);
				check = n1->node_pos->get_check_black();
				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);	
				}

			}
		}else if(value == BROOK && wb == BLACK){
			rook = new Rook(x, y, BLACK, ROOK, 8, 8);
			rook->set_pos(p);
			vector<Move>rmoves_black = rook->set_moves();
			vector<Node*>rnodes = get_nodes(rmoves_black, p, curr, !wb);
			if(rnodes.size() < 1){
				cout << "in generator: rook has no moves." << endl;
			}
			for(int t=0; t<rnodes.size(); t++){
				Node *n1 = rnodes[t];
				curr->add_child(n1);
				check = n1->node_pos->get_check_white();
				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);
				}
			}
		}
	}else if(value == WQUEEN || value == BQUEEN){
		cout << "in generator: queen" << endl;
		Queen *queen;
		if(value == BQUEEN && wb == BLACK){
			queen = new Queen(x, y, BLACK, QUEEN, 8, 8);
			queen->set_pos(p);
			vector<Move>qmoves = queen->set_moves();
			vector<Node*>tnodes = get_nodes(qmoves, p, curr, !wb);
			if(tnodes.size() < 1){
				cout << "in generator: queen has no moves. " << endl;
			}
			for(int t=0; t<tnodes.size(); t++){
				Node *n1 = tnodes[t];
				curr->add_child(n1); 
				check = n1->node_pos->get_check_white(); 

				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);
				}
			}
		}else if(value == WQUEEN && wb == WHITE){
			queen = new Queen(x, y, WHITE, QUEEN, 8, 8);
			queen->set_pos(p);
			vector<Move>qmoves = queen->set_moves();
			vector<Node*>tnodes = get_nodes(qmoves, p, curr, !wb);
			if(tnodes.size() < 1){
				cout << "in generator: queen has no moves." << endl;
			}
			for(int t=0; t<tnodes.size(); t++){
				Node *n1 = tnodes[t];
				curr->add_child(n1);
				check = n1->node_pos->get_check_black(); 

				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);
				}
			}
		}
	
	}else if(value == BKING || value == WKING){
		//king case, kings not in check. 
		King *king;
		if(value == BKING && wb == BLACK){
			king = new King(x, y, BLACK, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves();
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
			vector<Node *>tnodes = get_nodes(valid_moves, p, curr, !wb);
			if(tnodes.size() < 1){
				cout << "in generator: king has no moves." << endl;
			}
			for(int t=0; t<tnodes.size(); t++){
				Node *n1 = tnodes[t];
				curr->add_child(n1);
				check = n1->node_pos->get_check_white();

				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);
				}
			}
		}else if(value == WKING && wb == WHITE){
			king = new King(x, y, WHITE, KING, 1, 1);
			king->set_pos(p);
			vector<Move>kmoves = king->set_moves();
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
			vector<Node*>tnodes = get_nodes(valid_moves, p, curr, !wb);
			if(tnodes.size() < 1){
				cout << "in generator: king has no moves." << endl;
			}

			for(int t=0; t<tnodes.size(); t++){
				Node *n1 = tnodes[t];
				curr->add_child(n1);
				check = n1->node_pos->get_check_black();

				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);
				}
			}
		
		}
	} //all pieces added. 
     }else{ //check on the board.
                  //only king moves possible for person in check....
                  //if no king moves then mate is on the board.
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

			vector<Move>moves = king->set_moves(); 

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
			if(valid_moves.size() == 0){
				cout << "BLACK WINS BY CHECKMATE" << endl;
				curr->wb_ratio = -999;
				return; 
			}
			vector<Node *>nodes = get_nodes(valid_moves, p, curr, !wb);
			for(int t=0; t<nodes.size(); t++){
				Node *n1 = nodes[t];
				curr->add_child(n1);
				check = curr->node_pos->get_check_black(); 
				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check); 
				}
			}

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

			vector<Move>moves = king->set_moves();
			
			vector<Move>valid_moves;
			for(int i=0; i<moves.size(); i++){
				Move mi = moves[i];
				bool valid;
				for(int j=0; j<white_threats.size(); j++){
					Square sj = white_threats[j];
					if(sj.x == mi.x_end && sj.y == mi.y_end){
						valid = false;
					}
				}
				if(valid)
					valid_moves.push_back(mi);
			}
			if(valid_moves.size() == 0){
				cout << "WHITE WINS BY CHECKMATE" << endl;
				curr->wb_ratio = 999;
				return; 
			}
			vector<Node *>nodes = get_nodes(valid_moves, p, curr, !wb);
			for(int i=0; i<nodes.size(); i++){
				Node *n1 = nodes[i];
				curr->add_child(n1); 
				check = curr->node_pos->get_check_white(); 			
				if(depth+1 <= max_depth){
					build_tree(n1, depth+1, !wb, max_depth, check);
				}

			}


		  
		  }
     }

    }

    }
   }
  }else{
    cout << "depth reached." << endl;
    return;
  }

}

Node *Generator::get_tree_root(){
  return move_tree->root;
}
