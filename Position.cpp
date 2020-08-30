#include "Position.h"
#include "Piece.h"

using namespace std;


Position::Position() {
	board_pos = T1;
	for (int ii = 0; ii < 8; ii++) {
		for (int jj = 0; jj < 8; jj++) {
			the_board[ii][jj] = NULLCELL;
		}
	}

}

Position::Position(int b) {

	board_pos = b;

	for (int ii = 0; ii < 8; ii++) {
		for (int jj = 0; jj < 8; jj++) {
			the_board[ii][jj] = NULLCELL;
		}
	}


	int x = 0;
	int y = 0;

	if (b == START) {
		//TODO: build chess starting position.
	}
	else if (b == EMPTY) {
		//nothing needs to be done.
	}
	else if (b == T1) { //test position.
		the_board[6][1] = BPAWN;
		the_board[7][0] = WPAWN; 

		the_board[3][3] = WBISH;
		the_board[5][4] = BKNIGHT; 
	}
	else if (b == TEST_2) {
		for (y; y < 8; y++) {
			the_board[1][y] = BPAWN;
			the_board[6][y] = WPAWN;
		}
		the_board[2][3] = WKNIGHT;
		the_board[3][4] = BKNIGHT;

	}else if (b == TEST_3){
		for (y; y < 8; y++) {
			the_board[1][y] = BPAWN;
			the_board[6][y] = WPAWN;
		}
		the_board[0][0] = BBISH;
		the_board[7][7] = WBISH;
	}else if (b == TCHECK){
		the_board[0][0] = BROOK;
		the_board[0][3] = BKING;
		the_board[1][2] = BPAWN;	
		the_board[1][3] = BPAWN;	
		the_board[1][4] = BPAWN;
		the_board[2][3] = BKNIGHT;	
		
		
		the_board[6][5] = WPAWN;
		the_board[6][6] = WPAWN;
		the_board[6][7] = WPAWN;
		the_board[7][7] = WKING;
	}
}
