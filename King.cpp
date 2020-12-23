#include "King.h"
#define NULLCELL 3


using namespace std;

King::King(){
	x_diff = 1;
	y_diff = 1;
}

bool in_bounds(int x, int y){
	if(x <= 7 && x >= 0 && y>=0 && y<= 7){
		return true;
	}
	return false;
}

vector<Move> King::set_moves(bool threats){
	vector<Move>moves;
	vector<Move>tvec;
	if(is_pos_set && is_color_set){
		for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				if(i != 0 || j != 0){
					if(in_bounds(x+i, y+j)){
						int sq = pos->the_board[x+i][y+j];
						if(sq == NULLCELL){
							//need to check if its enemy controlled square.
							Move m(x+i, y+j, color, false, false, KING, x, y, false, false);
							moves.push_back(m); 
							tvec.push_back(m);
						}else if(is_enemy_piece_type(sq)){
							Move t(x+i, y+j, color, true, false, KING, x, y, false, false); 
							moves.push_back(t); 
						}else if(!is_enemy_king(sq)){
							Move t(x+i, y+j, color, true, false, KING, x, y, false, false);
							tvec.push_back(t); 
						}

					}
				}
			}
		}
		//castling
		if(color == BLACK){
			bool conA = (x == 0 && y == 4);
			int qs_rook = pos->the_board[0][0];
			int ks_rook = pos->the_board[0][7];

			bool conB = (qs_rook == BROOK);
			int mids1 = pos->the_board[0][1];
			int mids2 = pos->the_board[0][2];
			int mids3 = pos->the_board[0][3];

			bool conC = (mids1 == mids2 && mids3 == mids2 && mids1 == NULLCELL);

			if(conA && conB && conC){
				Move queenSideCastle(0, 2, color, false, false, KING, x, y, false, true);
				moves.push_back(queenSideCastle);
			}

			bool conD = (ks_rook == BROOK);

			mids1 = pos->the_board[0][6];
			mids2 = pos->the_board[0][5];

			bool conE = (mids1 == mids2 && mids1 == NULLCELL);

			if(conA && conD && conE){
				Move kingSideCastle(0, 6, color, false, false, KING, x, y, true, false);
				moves.push_back(kingSideCastle);
			}
		}else{ //color is white

			bool conA = (x == 7 && y == 4);
			int qs_rook = pos->the_board[7][0];
			int ks_rook = pos->the_board[7][7];

			bool conB = (qs_rook == WROOK);
			int mids1 = pos->the_board[7][1];
			int mids2 = pos->the_board[7][2];
			int mids3 = pos->the_board[7][3];

			bool conC = (mids1 == mids2 && mids3 == mids2 && mids1 == NULLCELL);

			if(conA && conB && conC){
				Move queenSideCastle(7, 2, color, false, false, KING, x, y, false, true);
				moves.push_back(queenSideCastle);
			}

			bool conD = (ks_rook == WROOK);

			mids1 = pos->the_board[7][6];
			mids2 = pos->the_board[7][5];

			bool conE = (mids1 == mids2 && mids1 == NULLCELL);

			if(conA && conD && conE){
				Move kingSideCastle(7, 6, color, false, false, KING, x, y, true, false);
				moves.push_back(kingSideCastle);
			}
		
		
		}
	
	}
	curr_moves = moves;
	if(threats)
		return tvec;
	return moves;
}
