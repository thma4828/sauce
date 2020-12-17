#include "Position.h"
#include "Piece.h"
#include <fstream>
#include <string> 
#include <iostream>
#include <sstream> 
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

	int y = 0;

	if (b == START) {
		//TODO: build chess starting position.
		for(int col = 0; col<8; col++){
			the_board[1][col] = BPAWN;

			the_board[6][col] = WPAWN;
		}

		the_board[0][0] = BROOK;
		the_board[0][1] = BKNIGHT;
		the_board[0][2] = BBISH;
		the_board[0][3] = BQUEEN;
		the_board[0][4] = BKING;
		the_board[0][5] = BBISH;
		the_board[0][6] = BKNIGHT;
		the_board[0][7] = BROOK;


		the_board[7][0] = WROOK;
		the_board[7][1] = WKNIGHT;
		the_board[7][2] = WBISH;
		the_board[7][3] = WQUEEN;
		the_board[7][4] = WKING;
		the_board[7][5] = WBISH;
		the_board[7][6] = WKNIGHT;
		the_board[7][7] = WROOK;
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
		the_board[0][0] = BROOK;
		the_board[0][4] = BKING;
		the_board[0][7] = BROOK;
		
		the_board[1][0] = BPAWN;
		the_board[1][1] = BPAWN;
		the_board[1][2] = BPAWN;
		the_board[1][4] = BQUEEN; 
		the_board[1][5] = BPAWN;
		the_board[1][6] = BBISH; 
		the_board[1][7] = BPAWN;
		
		the_board[2][2] = BKNIGHT;
		the_board[2][3] = BPAWN;
		the_board[2][5] = BKNIGHT;
		the_board[2][6] = BPAWN;

		the_board[3][4] = BPAWN;
		the_board[3][7] = BBISH;

		the_board[4][7] = WPAWN;
		
		the_board[5][1] = WPAWN;
		the_board[5][2] = WKNIGHT;
		the_board[5][3] = WPAWN;
		the_board[5][5] = WKNIGHT;

		the_board[6][0] = WPAWN;
		the_board[6][1] = WBISH;
		the_board[6][4] = WQUEEN;
		the_board[6][5] = WPAWN;

		the_board[7][2] = WKING;
		the_board[7][3] = WROOK;
		the_board[7][5] = WBISH;
		the_board[7][7] = WROOK;

	}else if (b == TCHECK){
		the_board[0][2] = BROOK;
		the_board[0][1] = BKING;
		the_board[1][0] = BPAWN;	
		the_board[1][1] = BPAWN;	
		the_board[1][2] = BPAWN;
		
		
		
		the_board[6][5] = WPAWN;
		the_board[6][6] = WPAWN;
		the_board[6][7] = WPAWN;
		the_board[7][6] = WKING;
		the_board[7][5] = WROOK; 
		the_board[4][4] = WQUEEN;
		the_board[5][5] = WBISH; 
	}else if(b == TCASTLE){
		the_board[0][4] = BKING;
		the_board[0][0] = BROOK;
		the_board[0][7] = BROOK;
		

		the_board[7][4] = WKING;
		the_board[7][0] = WROOK;
		the_board[7][7] = WROOK;
	
	}else if(b == TPUZZLE1){ //black to move
		//rank8
		the_board[0][0] = BROOK;		
		the_board[0][2] = BBISH;		
		the_board[0][4] = BKING;		
		the_board[0][6] = BKNIGHT;		
		the_board[0][7] = BROOK;		
		//rank7
		the_board[1][0] = BPAWN;
		the_board[1][1] = BPAWN;
		the_board[1][2] = BPAWN;
		the_board[1][3] = BPAWN;
		the_board[1][5] = BPAWN;
		the_board[1][6] = BPAWN;
		the_board[1][7] = BPAWN;
		//rank6
		the_board[2][3] = BBISH;
		the_board[2][5] = BQUEEN; 

		//rank4
		the_board[4][2] = WBISH;
		the_board[4][3] = WQUEEN; 
		the_board[4][4] = WPAWN;

		//rank3
		the_board[5][4] = WBISH;

		//rank2
		the_board[6][0] = WPAWN;
		the_board[6][1] = WPAWN;
		the_board[6][2] = WPAWN;
		the_board[6][5] = WPAWN;
		the_board[6][6] = WPAWN;
		the_board[6][7] = WPAWN;

		//rank1
		the_board[7][0] = WROOK;
		the_board[7][1] = WKNIGHT;
		the_board[7][4] = WKING;
		the_board[7][7] = WROOK; 

	}
}

void Position::read_board_file(string f){
    ifstream reader;
    reader.open(f);
    string line, token; 
    int i = 0;
    int j;
    if(!reader.is_open()){
	cout << "could not open board file." << endl; 		    
    }else{
    	while(getline(reader, line) && i < 8){
		istringstream iss(line); 
		j = 0;
		while(iss >> token && j < 8){
		   int piece_code = stoi(token);
		   j++;

		   the_board[i][j] = piece_code; 
		}
		i++;
	}
    }
}

Position::~Position(){
	//
}
