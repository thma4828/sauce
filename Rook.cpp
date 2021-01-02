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
		if(X < 7 && is_enemy_piece_type(pos->the_board[X+1][Y]) ){
			Move t_down(X+1, Y, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_down);
			threats.push_back(t_down); 
		}else if(X < 7 && !is_enemy_piece_type(pos->the_board[X+1][Y])){					  Move t_down(X+1, Y, color, true, false, ROOK, x, y, false, false);
			threats.push_back(t_down); 
		}
	


		
		X = x;
		while(Y < 7 && pos->the_board[X][Y+1] == NULLCELL){
			Move m_right(X, Y+1, color, false, false, ROOK, x, y, false, false);
			moves.push_back(m_right);
			threats.push_back(m_right);
			Y++;
		}
		
		if(Y < 7 && is_enemy_piece_type(pos->the_board[X][Y+1]) ){
			Move t_right(X, Y+1, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_right);
			threats.push_back(t_right); 
		}else if(Y < 7 && !is_enemy_piece_type(pos->the_board[X][Y+1])){
			Move t_right(X, Y+1, color, true, false, ROOK, x, y, false, false); 
			threats.push_back(t_right); 
		}


		Y = y;
		X = x;
		while(X > 0 && pos->the_board[X-1][Y] == NULLCELL){
			Move m_up(X-1, Y, color, false, false, ROOK, x, y, false, false);
			moves.push_back(m_up);
			threats.push_back(m_up);
			X--;
		}
		if(X > 0 && is_enemy_piece_type(pos->the_board[X-1][Y]) ){
			Move t_up(X-1, Y, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_up);
			threats.push_back(t_up); 
		}else if(X > 0 && !is_enemy_piece_type(pos->the_board[X-1][Y])){
			
			Move t_up(X-1, Y, color, true, false, ROOK, x, y, false, false);
			threats.push_back(t_up); 
		}
		
		X = x;
		while(Y > 0 && pos->the_board[X][Y-1] == NULLCELL){
			Move m_left(X, Y-1, color, false, false, ROOK, x,  y, false, false);
			moves.push_back(m_left);
			threats.push_back(m_left);
			Y--;
		}
		if(Y > 0 && is_enemy_piece_type(pos->the_board[X][Y-1]) ){
			Move t_left(X, Y-1, color, true, false, ROOK, x, y, false, false);
			moves.push_back(t_left);
			threats.push_back(t_left); 
		}else if(Y > 0 && !is_enemy_piece_type(pos->the_board[X][Y-1])){
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
