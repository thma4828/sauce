#include "Piece.h"
#include <iostream>

using namespace std;

Piece::Piece(int c) {
	color = c;
	is_color_set = true;
	is_null_piece = false;
	x = -1;
	y = -1;
	piece_type = NUL;
	x_diff = 0;
	y_diff = 0;
}

Piece::Piece() {
	color = NUL;
	is_color_set = false;
	is_null_piece = true;
	x = -1;
	y = -1;
	piece_type = NUL;
	x_diff = 0;
	y_diff = 0;
}

Piece::Piece(int a, int b) {
	color = NUL;
	is_color_set = false;
	is_null_piece = true;
	x = a;
	y = b;
	piece_type = NUL;
	x_diff = 0;
	y_diff = 0;
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

vector<Move> Piece::get_moves(int a, int b, void *) {
	vector<Move>res;
	return res;
}