#include "Piece.h"
#include <iostream>

using namespace std;

Piece::Piece(int c) {
	color = c;
	is_color_set = true;
	is_null_piece = false;
	x = -1;
	y = -1;
	piece_type = NONE;
	x_diff = 0;
	y_diff = 0;
	is_pos_set = false;
	pos = nullptr;
}

Piece::Piece() {
	color = NONE;
	is_color_set = false;
	is_null_piece = true;
	x = -1;
	y = -1;
	piece_type = NONE;
	x_diff = 0;
	y_diff = 0;
	is_pos_set = false;
	pos = nullptr;
}

Piece::Piece(int a, int b) {
	color = NONE;
	is_color_set = false;
	is_null_piece = true;
	x = a;
	y = b;
	piece_type = NONE;
	x_diff = 0;
	y_diff = 0;
	is_pos_set = false;
	pos = nullptr;
}

Piece::Piece(int a, int b, int c, int p, int yd, int xd) {
	piece_type = p;
	color = c;
	is_color_set = true;
	is_null_piece = false;
	x = a;
	y = b;
	x_diff = xd;
	y_diff = yd;
	is_pos_set = false;
	pos = nullptr;
}

int Piece::get_x_diff() {
	return x_diff;
}

int Piece::get_y_diff() {
	return y_diff;
}

int Piece::get_color_set() {
	return is_color_set;
}

int Piece::get_null_piece() {
	return is_null_piece;
}

void Piece::set_xy(int a, int b) {
	if (a > 7 || a < 0 || b > 7 || b < 0) {
		cerr << "error: invalid index to set piece location." << endl;
		exit(0);
	}
	x = a; y = b;
}
void Piece::set_color(int c) {
	color = c;
	is_color_set = true;
}

int Piece::get_x() {
	return x;
}

int Piece::get_y() {
	return y;
}

int Piece::get_color() {
	return color;
}

int Piece::get_piece_type() {
	return piece_type;
}

void Piece::set_pos(Position* p) {
	pos = p;
	is_pos_set = true;
}

vector<Move> Piece::get_moves() {
	return curr_moves;
}

void Piece::clear_moves() {
	curr_moves.clear();
}

int Piece::get_pos_status() {
	return is_pos_set;
}

vector<Move> Piece::set_moves() {
	vector<Move>a;
	return a;
}

int Piece::is_enemy_piece_type(int pc) {
	if (is_color_set) {
		if (color == BLACK) {
			if (pc == WPAWN || pc == WBISH || 
			    pc == WROOK || pc == WKNIGHT ||
			    pc == WQUEEN) { //add rest of enemy pieces. just Q, K and Night
				return 1;
			}
			else {
				return 0;
			}
		}
		else { //color is white, so enemy piece would be black piece....
			if (pc == BPAWN || pc == BBISH ||
			    pc == BROOK || pc == BKNIGHT || 
			    pc == BQUEEN) { //add rest of enemy pieces. just Q, K and Night
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	return -1;
}

int Piece::is_enemy_king(int pc) {
	if (is_color_set) {
		if (color == BLACK) {
			if (pc == WKING) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (pc == BKING) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return -1;
}
