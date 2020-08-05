#include "King.h"
#define NULLCELL 3


using namespace std;

King::King(){
	x_diff = 1;
	y_diff = 1;
}

vector<Move> King::set_moves(){
	vector<Move>moves;
	if(is_pos_set && is_color_set){
		cout << "in king set moves." << endl;
		for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				if(i != 0 || j != 0){
					int sq = pos->the_board[x+i][y+j];
					if(sq == NULLCELL){
						//need to check if its enemy controlled square.
						Move m(x+i, y+j, color, false, false, KING, x, y);
						moves.push_back(m); 
					}else if(is_enemy_piece_type(sq)){
						Move t(x+i, y+j, color, true, false, KING, x, y); 
						moves.push_back(t); 
					}
				}
			}
		}
	
	}
	curr_moves = moves;
	return moves;
}
