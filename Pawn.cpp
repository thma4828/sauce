#include "Pawn.h"


using namespace std;

Pawn::Pawn() {
	x_diff = 1;
	y_diff = 1;
}


vector<Move> Pawn::set_moves() {
	
	vector<Move>moves;
	if (is_pos_set && is_color_set && !is_null_piece) {
		if (color == BLACK) {
			
			if (x < 6) {
				
				if (y > 0 && y < 7) {
					
					if (pos->the_board[x + 1][y] == NULCELL) {
						Move m1(x + 1, y, BLACK, false, false, PAWN, x, y);
						
						moves.push_back(m1);

						if (x < 6) { // can only move forward 2 if it can move forward 1...
							if (pos->the_board[x + 2][y] == NULCELL) {
								Move m2(x + 2, y, BLACK, false, false, PAWN, x, y);
								
								moves.push_back(m2);
							}
						}
					}
					int enemy_squarex1y1 = pos->the_board[x + 1][y + 1];
					int enemy_squarex1y2 = pos->the_board[x + 1][y - 1];


					if (is_enemy_piece_type(enemy_squarex1y1) && !is_enemy_king(enemy_squarex1y1)){ //add all other enemy types.
						Move t1(x + 1, y + 1, BLACK, true, false, PAWN, x, y);
						moves.push_back(t1);
					}
					else if (is_enemy_king(enemy_squarex1y1)) {
						//check on the board. 
					}
					
					if (is_enemy_piece_type(enemy_squarex1y2) && !is_enemy_king(enemy_squarex1y2)){
						Move t2(x + 1, y - 1, BLACK, true, false, PAWN, x, y);
						moves.push_back(t2);
					}
					else if (is_enemy_king(enemy_squarex1y2)) {
						//check is on the board. 
						//it cannot be your turn unless the game is over. 
					}
				}
				else {
					if (y == 0) { // just cant take to any y to the left

					}
					else { //y is 7 cant take to the right. 

					}
				}
				
				
			}
			else if(x == 6){ // black pawn one move from being on the back rank and promoting 
				//a pawn promotion. 
				Move m_promote(x + 1, y, BLACK, false, true, PAWN, x, y);
				moves.push_back(m_promote);
			}
			else {
				//pawn on backrank that didn't choose to promote? or promoted to a pawn...?
			}
		}
		else { // color is WHITE
			//TODO same thing as done for black but reversed index transform. 
		}
	}
	else {
		cerr << "error: pawn not init properly" << endl;
	}
	curr_moves = moves;
	return moves;
}



int Pawn::get_piece_type() {
	return PAWN;
}
