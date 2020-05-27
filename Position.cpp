#include "Position.h"
#include "Piece.h"
#include "Pawn.h"
using namespace std;

Position::Position() {
	board_pos = T1;
}

Position::Position(int b) {

	for (int ii = 0; ii < 8; ii++) {
		for (int jj = 0; jj < 8; jj++) {
			the_board[ii][jj] = Piece();
		}
	}
	
	board_pos = b;
	int x = 0;
	int y = 0;

	if (b == START) {
		//TODO
	}
	else if (b == EMPTY) {
		for (x; x < 8; x++) {
			for (y; y < 8; y++) {
				the_board[x][y] = Piece(x, y);
			}
		}
	}
	else if (b == T1) { //test position.
		
		for (y; y < 8; y++) {
			the_board[1][y] = Pawn(x, y, BLACK, PAWN, 1, 1);
			the_board[6][y] = Pawn(x, y, WHITE, PAWN, 1, 1);
		}
	}
}
