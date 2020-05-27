#include "Position.h"

using namespace std;
#define WPAWN 31
#define BPAWN 34
#define NULCELL 58

Position::Position() {
	board_pos = T1;
}

Position::Position(int b) {

	board_pos = b;

	for (int ii = 0; ii < 8; ii++) {
		for (int jj = 0; jj < 8; jj++) {
			the_board[ii][jj] = WPAWN;
		}
	}
	
	
	int x = 0;
	int y = 0;

	if (b == START) {
		//TODO
	}
	else if (b == EMPTY) {
		for (x; x < 8; x++) {
			for (y; y < 8; y++) {
				the_board[x][y] = NULCELL;
			}
		}
	}
	else if (b == T1) { //test position.
		
		for (y; y < 8; y++) {
			the_board[1][y] = BPAWN;
			the_board[6][y] = WPAWN;
		}
	}
}
