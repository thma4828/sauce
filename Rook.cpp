#include "Rook.h"
#include "Piece.h"
#include "Move.h"
#include <iostream>
#include <cassert>

using namespace std;


Rook::Rook(){
	x_diff = 8;
	y_diff = 8;
}


int Rook::get_piece_type(){
	return ROOK;
}

vector<Move> Rook::set_moves(bool threats){
	vector<Move>moves;
	if(is_color_set && is_pos_set && !is_null_piece){
		cout << "in rook: set moves." << endl;
	
		int X, Y;
		X = x;
		Y = y;
		while(X < 7 && pos->the_board[X+1][Y] == NULLCELL){
			Move m_down(X+1, Y, color, false, false, ROOK, x, y);
			moves.push_back(m_down);
			X++;
		}
		if( is_enemy_piece_type(pos->the_board[X+1][Y]) ){
			Move t_down(X+1, Y, color, true, false, ROOK, x, y);
			moves.push_back(t_down);
		} 
		
		X = x;
		while(Y < 7 && pos->the_board[X][Y+1] == NULLCELL){
			Move m_right(X, Y+1, color, false, false, ROOK, x, y);
			moves.push_back(m_right);
			Y++;
		}
		
		if( is_enemy_piece_type(pos->the_board[X][Y+1]) ){
			Move t_right(X, Y+1, color, true, false, ROOK, x, y);
			moves.push_back(t_right);
		}

		Y = y;
		X = x;
		while(X > 0 && pos->the_board[X-1][Y] == NULLCELL){
			Move m_up(X-1, Y, color, false, false, ROOK, x, y);
			moves.push_back(m_up);
			X--;
		}
		if( is_enemy_piece_type(pos->the_board[X-1][Y]) ){
			Move t_up(X-1, Y, color, true, false, ROOK, x, y);
			moves.push_back(t_up);
		}
		X = x;
		while(Y > 0 && pos->the_board[X][Y-1] == NULLCELL){
			Move m_left(X, Y-1, color, false, false, ROOK, x,  y);
			moves.push_back(m_left);
			Y--;
		}
		if( is_enemy_piece_type(pos->the_board[X][Y-1]) ){
			Move t_left(X, Y-1, color, true, false, ROOK, x, y);
			moves.push_back(t_left);
		}
			
	
	}else{
		cout << "rook piece not initialized." << endl;
	}
	
	curr_moves = moves;
	return moves;
}
