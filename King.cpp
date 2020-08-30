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
							Move m(x+i, y+j, color, false, false, KING, x, y);
							moves.push_back(m); 
							tvec.push_back(m);
						}else if(is_enemy_piece_type(sq)){
							Move t(x+i, y+j, color, true, false, KING, x, y); 
							moves.push_back(t); 
						}else if(!is_enemy_king(sq)){
							Move t(x+i, y+j, color, true, false, KING, x, y);
							tvec.push_back(t); 
						}

					}
				}
			}
		}
	
	}
	curr_moves = moves;
	if(threats)
		return tvec;
	return moves;
}
