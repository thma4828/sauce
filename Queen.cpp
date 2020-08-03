#include "Queen.h"
#define NULLCELL 3

using namespace std;


Queen::Queen(){
	x_diff = 8;
	y_diff = 8;
}


vector<Move> Queen::set_moves(){
	vector<Move>moves;
	if(is_pos_set && is_color_set){
		cout << "in queen set moves." << endl;
		int X = x;
		int Y = y;
		while(X > 0){
			X--;
			int sq = pos->the_board[X][Y];
			if(sq == NULLCELL){
				Move m1(X, Y, color, false, false, QUEEN, x, y);
				moves.push_back(m1);

			}else if(is_enemy_piece_type(sq)){
				Move t1(X, Y, color, true, false, QUEEN, x, y); 
				moves.push_back(t1);
				break;
			}
		
		}
		X = x;
	 	while(X < 7){
			X++;
			int sq = pos->the_board[X][Y];
			if(sq == NULLCELL){
				Move m1(X, Y, color, false, false, QUEEN, x, y);
				moves.push_back(m1);
			}else if(is_enemy_piece_type(sq)){
				Move t1(X, Y, color, true, false, QUEEN, x, y); 
				moves.push_back(t1);
				break; 
			}
		}	
	}

	curr_moves = moves;
	return moves;
}
