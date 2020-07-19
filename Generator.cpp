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

vector<Node*> Generator::get_nodes(vector<Move>moves, Position *p, Node *curr, int wb){
  vector<Node*>nodes;
  cout << "in generator: get_nodes(): entering routine." << endl;
  for(int j=0; j<moves.size(); j++){
    cout << "in generator: get_nodes(): for loop iter: " << j << endl;
    Move m = moves[j];
    //create a node in the tree for position created by this move.
    Node *n1 = new Node(curr, wb, 0.1, 0.1);
    Board *b1 = new Board();
    //need a new position same as *p but with move m added
    cout << "------>iter " << j << ": node and board initialized in memory" << endl;
    cout << "------>iter " << j << ": move has x_start, y_start = (" <<
    m.x_start << "," << m.y_start << ")"<<endl;
    cout << "------>iter " << j << ": move has x_end, y_end = (" <<
    m.x_end << "," << m.y_end << ")"<<endl;
    int piece2move = p->the_board[m.x_start][m.y_start];
    cout << "------>iter " << j << ": Piece to move is of code: " << piece2move << endl;
    Position *pnew = new Position();
    cout << "------>iter " << j << ": going into 8x8 double for loop to copy most of position over." << endl;
    for(int x=0; x<8; x++){
      for(int y=0; y<8; y++){

          pnew->the_board[x][y] = p->the_board[x][y];

      }
    }
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
            vector<Move>kmoves;
            vector<Node*>tnodes;
            if(value == BKNIGHT && wb == BLACK){
                knight = new Knight(x, y, BLACK, KNIGHT, 2, 3);
                knight->set_pos(p);
                knight->set_moves();
                kmoves = knight->get_moves();
		if(kmoves.size() < 1)
			cout << "in generator: knight, black knight has no moves" << endl;
                tnodes = get_nodes(kmoves, p, curr, !wb);
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
              knight->set_moves();
              kmoves = knight->get_moves();
	      if(kmoves.size() < 1)
		      cout << "in generator: knight: white night has no moves." << endl;
              tnodes = get_nodes(kmoves, p, curr, !wb);

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
            }
        }else{ //check on the board.
                  //only king moves possible for person in check....
                  //if no king moves then mate is on the board.
                  //board could have a functionality to check for mate in these situations.
                  //or I suppose if simply it is check and the king move vector comes
                  //back empty.
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
