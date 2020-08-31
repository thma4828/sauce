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

vector<Move> Rook::set_moves(bool t){
	vector<Move>moves;
	vector<Move>threats; 
	if(is_color_set && is_pos_set && !is_null_piece){
	
		int X, Y;
		X = x;
		Y = y;
		while(X < 7 && pos->the_board[X+1][Y] == NULLCELL){
			Move m_down(X+1, Y, color, false, false, ROOK, x, y, false, false);
			moves.push_back(m_down);
			threats.push_back(m_down);
			X++;
		}
		if( is_enemy_piece_type(pos->the_board[X+1][Y]) ){
			Move t_down(X+1, Y, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_down);
		}
		if(X < 7){
			Move t1(X+1, Y, color, true, false, ROOK, x, y, false, false); //gaurding friendly
			threats.push_back(t1); 
		}


		
		X = x;
		while(Y < 7 && pos->the_board[X][Y+1] == NULLCELL){
			Move m_right(X, Y+1, color, false, false, ROOK, x, y, false, false);
			moves.push_back(m_right);
			threats.push_back(m_right);
			Y++;
		}
		
		if( is_enemy_piece_type(pos->the_board[X][Y+1]) ){
			Move t_right(X, Y+1, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_right);
		}
		if(Y < 7){
			Move t2(X, Y+1, color, true, false, ROOK, x, y, false, false);
			threats.push_back(t2); 
		}

		Y = y;
		X = x;
		while(X > 0 && pos->the_board[X-1][Y] == NULLCELL){
			Move m_up(X-1, Y, color, false, false, ROOK, x, y, false, false);
			moves.push_back(m_up);
			threats.push_back(m_up);
			X--;
		}
		if( is_enemy_piece_type(pos->the_board[X-1][Y]) ){
			Move t_up(X-1, Y, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_up);
		}
		if(X > 0){
			Move t3(X-1, Y, color, true, false, ROOK, x, y, false, false);
			threats.push_back(t3); 
		}
		X = x;
		while(Y > 0 && pos->the_board[X][Y-1] == NULLCELL){
			Move m_left(X, Y-1, color, false, false, ROOK, x,  y, false, false);
			moves.push_back(m_left);
			threats.push_back(m_left);
			Y--;
		}
		if( is_enemy_piece_type(pos->the_board[X][Y-1]) ){
			Move t_left(X, Y-1, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_left);
			threats.push_back(t_left); 
		}if(Y > 0){
			Move t4(X, Y-1, color, true, false, ROOK, x, y, false, false); 
			threats.push_back(t4);
		}
			
	
	}else{
	}
	
	curr_moves = moves;
	if(t)
		return threats;
	else
		return moves;
}
