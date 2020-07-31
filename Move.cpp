#include "Move.h"
#include <string>
#include "Piece.h"
using namespace std;

Move::Move(int xe, int ye, int cc, int ist, int isp, int pt, int xs, int ys) {
	x_end = xe;
	y_end = ye;
	x_start = xs;
	y_start = ys;
	color = cc;
	is_take = ist;
	is_promote = isp;
	piece_type = pt;
}

string Move::get_move_string(){
	string s;
	if(piece_type == PAWN){
		//
	}else if(piece_type == BISHOP){
		s.push_back('B');
	}else if(piece_type == KNIGHT){
		s.push_back('N');
	}else if(piece_type == ROOK){
		s.push_back('R');
	}

	if(is_take){
		s.push_back('x');
	}
	if(y_end == 0){
		s.push_back('a');	
	}
	if(y_end == 1){
		s.push_back('b');
	}
	if(y_end == 2){
		s.push_back('c');
	}
	if(y_end == 3){
		s.push_back('d');
	}
	if(y_end == 4){
		s.push_back('e');
	}
	if(y_end == 5){
		s.push_back('f');
	}
	if(y_end == 6){
		s.push_back('g');
	}
	if(y_end == 7){
		s.push_back('h');
	}

	int x_val = 8 - x_end;
	string xs = to_string(x_val);
	s.push_back(xs[0]);

	return s;
}
