#include "Board.h"



using namespace std;

Board::Board(){
  pos_eval_black = 1.0;
  pos_eval_white = 1.0;

  mat_eval_black = 1.0;
  mat_eval_white = 1.0; 
}

Board::~Board(){
	delete position; 
}

void Board::set_color(int c){
  color = c;
}

void Board::set_position_ep_squares(vector<vector<int>>sqs, int wb){
	if(wb == BLACK){
		position->ep_squares_black = sqs;
	}else if(wb == WHITE){
		position->ep_squares_white = sqs;
	}
}

vector<vector<int>> Board::get_position_ep_squares(int wb){
	if(wb == BLACK){
		return position->ep_squares_black; 
	}else if(wb == WHITE){
		return position->ep_squares_white; 
	}
	return position->ep_squares_white; 
}

vector<Square> Board::get_threat_squares(int col){
	if(col == WHITE){
		return black_threat_squares;
	}else{
		return white_threat_squares; 
	}
}

bool Board::get_check_white(){
  if(black_threat_squares.size() > 0)
	  black_threat_squares.clear();
  //TODO determine if check is in the pos on whites king.
  int kx, ky;
  kx = -1;
  ky = -1;
  for(int i=0; i<8; i++){
  	for(int j=0; j<8; j++){
		int p = position->the_board[i][j];
		if(p == WKING){
			kx = i;
			ky = j;
		}
	}
  }
  if((kx == -1) || (ky == -1)){
  	return false; 
  }
  bool is_check = false;
  for(int i=0; i<8; i++){
  	for(int j=0; j<8; j++){
		int p = position->the_board[i][j];
		if(p == BPAWN){
			Pawn *bpawn = new Pawn(i, j, BLACK, PAWN, 1, 1);
			bpawn->set_pos(position);
			vector<Move>moves = bpawn->set_moves(true);
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end);
				black_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 		
				}
			}
		}else if(p == BKNIGHT){
			Knight *knight = new Knight(i, j, BLACK, KNIGHT, 2, 3);
			knight->set_pos(position);
			vector<Move>moves = knight->set_moves(true); 
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end);
				black_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
			
		}else if(p == BBISH){
			Bishop *bish = new Bishop(i, j, BLACK, BISHOP, 8, 8);
			bish->set_pos(position);
			vector<Move>moves = bish->set_moves(true);
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end);
				black_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		}else if(p == BQUEEN){
			Queen *queen = new Queen(i, j, BLACK, QUEEN, 8, 8);
			queen->set_pos(position);
			vector<Move>moves = queen->set_moves(true);
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end);
				black_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		
		}else if(p == BROOK){
			Rook *rook = new Rook(i, j, BLACK, ROOK, 8, 8);
			rook->set_pos(position); 
			vector<Move>moves = rook->set_moves(true); 
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end); 
				black_threat_squares.push_back(s); 
			
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		}else if(p == BKING){
			King *king = new King(i, j, BLACK, KING, 1, 1); 
			king->set_pos(position);
			vector<Move>moves = king->set_moves(true);
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end);
				black_threat_squares.push_back(s);
				//cant be in check from the enemies king....
			}
		}
	}
  }
  return is_check;
}

bool Board::get_check_black(){
  if(white_threat_squares.size() > 0)
	  white_threat_squares.clear(); 
  int kx = -1;
  int ky = -1;
  for(int i=0; i<8; i++){
  	for(int j=0; j<8; j++){
		int p = position->the_board[i][j];
		if(p == BKING){
			kx = i; ky = j; 
		}
	}
  }
  if((kx == -1) || (ky == -1)){
  	return false; 
  }

  bool is_check = false;
  for(int i=0; i<8; i++){
  	for(int j=0; j<8; j++){
		int p = position->the_board[i][j];
		if(p == WPAWN){
			Pawn *pawn = new Pawn(i, j, WHITE, PAWN, 1, 1);
			pawn->set_pos(position);
			vector<Move>moves = pawn->set_moves(true); 
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end); 
				white_threat_squares.push_back(s);
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		}else if(p == WKNIGHT){
			Knight *knight = new Knight(i, j, WHITE, KNIGHT, 2, 3);
			knight->set_pos(position);
			vector<Move>moves = knight->set_moves(true); 
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end); 
				white_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		
		}else if(p == WQUEEN){
			Queen *queen = new Queen(i, j, WHITE, QUEEN, 8, 8);
			queen->set_pos(position);
			vector<Move>moves = queen->set_moves(true);
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end);
				white_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		
		}else if(p == WROOK){
			Rook *rook = new Rook(i, j, WHITE, ROOK, 8, 8);
			rook->set_pos(position);
			vector<Move>moves = rook->set_moves(true); 
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end); 
				white_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		
		}else if(p == WBISH){
			Bishop *bishop = new Bishop(i, j, WHITE, BISHOP, 8, 8);
			bishop->set_pos(position);
			vector<Move>moves = bishop->set_moves(true); 
			for(int m=0; m<moves.size(); m++){
				Move mi = moves[m];
				Square s(mi.x_end, mi.y_end); 
				white_threat_squares.push_back(s); 
				if(mi.x_end == kx && mi.y_end == ky){
					is_check = true; 
				}
			}
		
		}else if(p == WKING){
			King *king = new King(i, j, WHITE, KING, 1, 1);
			king->set_pos(position);
			vector<Move>moves = king->set_moves(true);
			for(int i=0; i<moves.size(); i++){
				Move mi = moves[i];
				Square s(mi.x_end, mi.y_end); 
				white_threat_squares.push_back(s); 
			}
		}
	}
  }
  return is_check;
}

bool Board::is_white(){
  if(color == WHITE)
    return true;
  else
    return false;
}
bool Board::is_black(){
  return !is_white();
}

void Board::set_position(Position *p){
  position = p;
}

void Board::calc_final_eval(){
  //TODO: without looking at future positions just give naive evaluation...
  //start with adding up piece totals...
  //if check on the board worth something.
  //if checkmate worth some const INF
  for(int x=0; x<8; x++){
    for(int y=0; y<8; y++){
      int piece_code = position->the_board[x][y];
      if(piece_code == WPAWN){
        mat_eval_white += 1.0;
      }
      if(piece_code == BPAWN){
        mat_eval_black += 1.0;
      }
      if(piece_code == WKNIGHT){
        mat_eval_white += 3.0;
     }
      if(piece_code == BKNIGHT){
        mat_eval_black += 3.0;
      }
      if(piece_code == WBISH){
        mat_eval_white += 3.0;
      }
      if(piece_code == BBISH){
        mat_eval_black += 3.0;
	
      }
      if(piece_code == WROOK){
        mat_eval_white += 5.0;
      }
      if(piece_code == BROOK){
        mat_eval_black += 5.0;
      }
      if(piece_code == WQUEEN){
        mat_eval_white += 9.0;
	
      }
      if(piece_code == BQUEEN){
        mat_eval_black += 9.0;
      }
      if(piece_code == WKING){
      	mat_eval_white += 41.0;

      }
      if(piece_code == BKING){
      	mat_eval_black += 41.0; 
      }

    }
  }
}
double  Board::get_wb_ratio(){
  return (mat_eval_white - mat_eval_black) + (0.25 * (pos_eval_white - pos_eval_black));
}
double Board::get_black(){
  return mat_eval_black;
}
double Board::get_white(){
  return mat_eval_white;
}

Position *Board::get_position(){
  return position;
}
