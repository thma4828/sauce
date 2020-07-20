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

vector<Move> Bishop::set_moves() {
	vector<Move>moves;
	if (pos != nullptr) {

		cout << "in bishop's version of get moves" << endl;
		if (is_color_set) {
			int X, Y;
			X = x;
			Y = y;
			while (X < 7 && Y < 7 && pos->the_board[X + 1][Y + 1] == NULLCELL) {
				Move d(X + 1, Y + 1, color, false, false, BISHOP, x, y);
				moves.push_back(d);
				X++;
				Y++;
			}

			if (X < 7 && Y < 7 && is_enemy_piece_type(pos->the_board[X + 1][Y + 1])) {
				Move t(X + 1, Y + 1, color, true, false, BISHOP, X, Y);
				moves.push_back(t);
			}
			else if (X < 7 && Y < 7 && is_enemy_king(pos->the_board[X + 1][Y + 1])) {
				//bishop is putting the king in check.
			}
			X = x;
			Y = y;
			while (X > 0 && Y > 0 && pos->the_board[X - 1][Y - 1] == NULLCELL) {
				Move d(X - 1, Y - 1, color, false, false, BISHOP, x, y);
				moves.push_back(d);
				X--;
				Y--;
			}

			if (X > 0 && Y > 0 && is_enemy_piece_type(pos->the_board[X - 1][Y - 1])) {
				Move t1(X - 1, Y - 1, color, true, false, BISHOP, X, Y);
				moves.push_back(t1);
			}
			else if (X > 0 && Y > 0 && is_enemy_king(pos->the_board[X - 1][Y - 1])) {
				//bishop is putting the king in check.
			}
			X = x;
			Y = y;
			while (X > 0 && Y < 7 && pos->the_board[X - 1][Y + 1] == NULLCELL) {
				Move d(X - 1, Y + 1, color, false, false, BISHOP, x, y);
				moves.push_back(d);
				X--;
				Y++;
			}
			if (X > 0 && Y < 7 && is_enemy_piece_type(pos->the_board[X - 1][Y + 1])) {
				Move t1(X - 1, Y + 1, color, true, false, BISHOP, X, Y);
				moves.push_back(t1);
			}
			else if (X > 0 && Y < 7 && is_enemy_king(pos->the_board[X - 1][Y + 1])) {
				//bishop is putting the king in check.
			}
			X = x;
			Y = y;
			while (X < 7 && Y > 0 && pos->the_board[X + 1][Y - 1] == NULLCELL) {
				Move d(X + 1, Y - 1, color, false, false, BISHOP, x, y);
				moves.push_back(d);
				X++;
				Y--;
			}
			if (is_enemy_piece_type(pos->the_board[X + 1][Y - 1])) {
				Move t2(X + 1, Y - 1, color, true, false, BISHOP, X, Y);
				moves.push_back(t2);
			}
			else if (X < 7 && Y > 0 && is_enemy_king(pos->the_board[X + 1][Y - 1])) {
				//bishop is putting the king in check.
			}
		}

	}
	curr_moves = moves;
	return moves;

}
