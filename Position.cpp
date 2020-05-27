#include "Position.h"

using namespace std;


Position::Position(int b) {

	for (int ii = 0; ii < 8; ii++) {
		for (int jj = 0; jj < 8; jj++) {
			A[ii][jj] = Piece();
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
				A[x][y] = Piece(x, y);
			}
		}
	}
	else if (b == T1) { //test position.
		
		for (y; y < 8; y++) {
			A[1][y] = Pawn(x, y, BLACK, PAWN);
			A[6][y] = Pawn(x, y, WHITE, PAWN);
		}
	}
}
