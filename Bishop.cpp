#include "Bishop.h"

#include <cassert>

#define NULLCELL 3

int Bishop::get_piece_type() {
	return BISHOP;
}
//constructor 1
Bishop::Bishop() {
	x_diff = 8;
	y_diff = 8;
}

vector<Move> Bishop::set_moves(bool threats){
	vector<Move>guarded;
	vector<Move>moves;
	if (is_color_set && is_pos_set && !is_null_piece) {

	//	cout << "in bishop's version of get moves" << endl;
		if (is_color_set) {
			int X, Y;
			X = x;
			Y = y;
			while (X < 7 && Y < 7 && pos->the_board[X + 1][Y + 1] == NULLCELL) {
				Move d(X + 1, Y + 1, color, false, false, BISHOP, x, y, false, false);
				moves.push_back(d);
				guarded.push_back(d);
				X++;
				Y++;
	//			cout << "bishop added move" << endl;
			}

			if (X < 7 && Y < 7 && is_enemy_piece_type(pos->the_board[X + 1][Y + 1])) {
				Move t(X + 1, Y + 1, color, true, false, BISHOP, x, y, false, false);
				moves.push_back(t);
				guarded.push_back(t); 
	//			cout << "bishop added take" << endl;
			}else if(X < 7 && Y < 7 && is_friendly_piece_type(pos->the_board[X+1][Y+1])){
			//gaurding friendly piece
				Move g(X + 1, Y + 1, color, true ,false ,BISHOP, x, y, false, false);
				guarded.push_back(g); 
			}
			
			X = x;
			Y = y;
			while (X > 0 && Y > 0 && pos->the_board[X - 1][Y - 1] == NULLCELL) {
				Move d(X - 1, Y - 1, color, false, false, BISHOP, x, y, false, false);
				moves.push_back(d);
				guarded.push_back(d);
				X--;
				Y--;
			}
			
			if (X > 0 && Y > 0 && is_enemy_piece_type(pos->the_board[X - 1][Y - 1])) {
				Move t1(X - 1, Y - 1, color, true, false, BISHOP, x, y, false, false);
				moves.push_back(t1);
				guarded.push_back(t1); 
			}else if(X > 0 && Y > 0 && is_friendly_piece_type(pos->the_board[X - 1][Y - 1])){
				Move g1(X - 1, Y - 1, color, true, false, BISHOP, x, y, false, false);
				guarded.push_back(g1);
			}
			
			X = x;
			Y = y;
			while (X > 0 && Y < 7 && pos->the_board[X - 1][Y + 1] == NULLCELL) {
				Move d(X - 1, Y + 1, color, false, false, BISHOP, x, y, false, false);
				moves.push_back(d);
				guarded.push_back(d); 
				X--;
				Y++;
			}
			if (X > 0 && Y < 7 && is_enemy_piece_type(pos->the_board[X - 1][Y + 1])) {
				Move t1(X - 1, Y + 1, color, true, false, BISHOP, x, y, false, false);
				moves.push_back(t1);
				guarded.push_back(t1); 
			}else if(X > 0 && Y < 7 && is_friendly_piece_type(pos->the_board[X - 1][Y + 1])){
				Move g1(X -1, Y + 1, color, true, false, BISHOP, x, y, false, false);
				guarded.push_back(g1);
			}
			
			X = x;
			Y = y;
			while (X < 7 && Y > 0 && pos->the_board[X + 1][Y - 1] == NULLCELL) {
				Move d(X + 1, Y - 1, color, false, false, BISHOP, x, y, false, false);
				moves.push_back(d);
				guarded.push_back(d);
				X++;
				Y--;
			}
			if (X < 7 && Y > 0 && is_enemy_piece_type(pos->the_board[X + 1][Y - 1])) {
				Move t2(X + 1, Y - 1, color, true, false, BISHOP, x, y, false, false);
				moves.push_back(t2);
				guarded.push_back(t2); 
			}else if(X < 7 && Y > 0 && is_friendly_piece_type(pos->the_board[X + 1][Y - 1])){
				Move g2(X + 1,  Y - 1, color, true, false, BISHOP, x, y, false, false);
				guarded.push_back(g2); 
			}
	
		}

	}
	curr_moves = moves;
	if(threats)
		return guarded;
	return moves;

}
