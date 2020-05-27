#include "Pawn.h"
#include <iostream>
#include <vector>

using namespace std;

Pawn::Pawn() {
	x_diff = 1;
	y_diff = 1;
}

vector<Move> Pawn::get_moves(int x, int y, Position *pos) { //x is verticle direction not horizontal
	vector<Move>moves;
	Move f1;
	f1.x = x + (x_diff * color); //black moves forward in +X direction
	f1.y = y;
	f1.is_take = false;
	f1.color = color; //this.color

	Move f2;
	f2.x = x + (x_diff * 2 * color);
	f2.y = y;
	f2.is_take = false;
	f2.color = color;

	
	if (is_color_set) {
		if (color == BLACK) { //black pawn
			if (x < 6) {
				if (pos->the_board[x + 1][y].get_null_piece()) {
					moves.push_back(f1);
					if (pos->the_board[x + 2][y].get_null_piece()) {
						moves.push_back(f2);
					}
				}
			}
		}
		else { 
			if (x > 1) {
				if (pos->the_board[x - 1][y].get_null_piece()) {
					moves.push_back(f1);
					if (pos->the_board[x - 2][y].get_null_piece()) {
						moves.push_back(f2);
					}
				}
			}
		}
	}
	return moves;
}

int Pawn::get_piece_type() {
	return PAWN;
}

