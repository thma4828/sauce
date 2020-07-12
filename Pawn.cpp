#include "Pawn.h"
#define NULLCELL 3

using namespace std;

Pawn::Pawn() {
	x_diff = 1;
	y_diff = 1;
}


vector<Move> Pawn::set_moves() {

	vector<Move>moves;
	if (is_pos_set && is_color_set && !is_null_piece) {
		if (color == BLACK) {
			cout << "in pawn set moves black" << endl;
			if (x < 6) {
					if (y > 0 && y < 7) {
						cout << "x < 6 and y not on 1st or 8th rank" << endl;
						if (pos->the_board[x + 1][y] == NULLCELL) {
							Move m1(x + 1, y, BLACK, false, false, PAWN, x, y);
							moves.push_back(m1);
							if (pos->the_board[x + 2][y] == NULLCELL) {
									Move m2(x + 2, y, BLACK, false, false, PAWN, x, y);
									moves.push_back(m2);
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
					} //x is still less than 6 and y is 7 or 0
					else {
						if (y == 0) { // just cant take to any y to the left
								cout << "in x<6 and y == 0" << endl;
								if(pos->the_board[x+1][y] == NULLCELL){
									cout <<"empty square for a move x+1 ahead." << endl;
									cout << "in x<6 and y == 0" << endl;
									Move ma(x+1, y, BLACK, false, false, PAWN, x, y);
									moves.push_back(ma);

									if(pos->the_board[x+2][y] == NULLCELL){
										Move mb(x+2, y, BLACK, false, false, PAWN, x, y);

										moves.push_back(mb);
									}
									moves.push_back(ma);
								}else{
									//pawn cannot move forward.
									cout << "pawn is obstructed" << endl;
									cout << "by piece with code: " << pos->the_board[x+1][y] << endl;
								}
								int enemy_s1 = pos->the_board[x+1][y+1];
								if(is_enemy_piece_type(enemy_s1) && !is_enemy_king(enemy_s1)){
									Move ta(x+1, y+1, BLACK, true, false, PAWN, x, y);
									moves.push_back(ta);
								}
						}
						else { //y is 7 cant take to the right. x still less than 6
							if(pos->the_board[x+1][y] == NULLCELL){
								Move ma(x+1, y, BLACK, false, false, PAWN, x, y);
								moves.push_back(ma);

								if(pos->the_board[x+2][y] == NULLCELL){
									Move mb(x+2, y, BLACK, false, false, PAWN, x, y);

									moves.push_back(mb);
								}
								moves.push_back(ma);
							}
							int enemy_s1 = pos->the_board[x+1][y-1];
							if(is_enemy_piece_type(enemy_s1) && !is_enemy_king(enemy_s1)){
								Move tb(x+1, y-1, BLACK, true, false, PAWN, x, y);
								moves.push_back(tb);
							}

						}
					}
			}
			else if(x == 6){ // black pawn one move from being on the back rank and promoting
				//a pawn promotion.
				//also breaks into subcases of y...
				int e;
				Move m_promote(x + 1, y, BLACK, false, true, PAWN, x, y);
				if(pos->the_board[x+1][y] == NULLCELL){
					moves.push_back(m_promote);
				}

				if(y > 0 && y < 7){
					Move mp2(x+1, y+1, BLACK, true, true, PAWN, x, y);
					e = pos->the_board[x+1][y+1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp2);
					}
					Move mp3(x+1, y-1, BLACK, true, true, PAWN, x, y);
					e = pos->the_board[x+1][y-1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp3);
					}


				}else if(y == 0){
					Move mp2(x+1, y+1, BLACK, true, true, PAWN, x, y);
					e = pos->the_board[x+1][y+1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp2);
					}
				}else{
					Move mp3(x+1, y-1, BLACK, true, true, PAWN, x, y);
					e = pos->the_board[x+1][y-1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp3);
					}
				}

			}//X is 7
			else {
				//pawn on backrank that didn't choose to promote? or promoted to a pawn...?
			}
		}
		else { // color is WHITE
			cout << "in pawn set moves black" << endl;
			//TODO same thing as done for black but reversed index transform.
			if (x > 1) {
					if (y > 0 && y < 7) {
						if (pos->the_board[x - 1][y] == NULLCELL) {
							Move m1(x - 1, y, WHITE, false, false, PAWN, x, y);
							moves.push_back(m1);
							if (pos->the_board[x - 2][y] == NULLCELL) {
									Move m2(x - 2, y, WHITE, false, false, PAWN, x, y);
									moves.push_back(m2);
							}
						}
						int enemy_squarex1y1 = pos->the_board[x - 1][y + 1];
						int enemy_squarex1y2 = pos->the_board[x - 1][y - 1];


						if (is_enemy_piece_type(enemy_squarex1y1) && !is_enemy_king(enemy_squarex1y1)){ //add all other enemy types.
							Move t1(x - 1, y + 1, WHITE, true, false, PAWN, x, y);
							moves.push_back(t1);
						}
						else if (is_enemy_king(enemy_squarex1y1)) {
							//check on the board.
						}

						if (is_enemy_piece_type(enemy_squarex1y2) && !is_enemy_king(enemy_squarex1y2)){
							Move t2(x - 1, y - 1, WHITE, true, false, PAWN, x, y);
							moves.push_back(t2);
						}
						else if (is_enemy_king(enemy_squarex1y2)) {
							//check is on the board.
							//it cannot be your turn unless the game is over.
						}
					} //x is still greater than 1, so not 1 from back rank
					else {
						if (y == 0) { // just cant take to any y to the left
								if(pos->the_board[x-1][y] == NULLCELL){
									Move ma(x-1, y, WHITE, false, false, PAWN, x, y);
									moves.push_back(ma);

									if(pos->the_board[x-2][y] == NULLCELL){
										Move mb(x-2, y, WHITE, false, false, PAWN, x, y);

										moves.push_back(mb);
									}
									moves.push_back(ma);
								}
								int enemy_s1 = pos->the_board[x-1][y+1];
								if(is_enemy_piece_type(enemy_s1) && !is_enemy_king(enemy_s1)){
									Move ta(x-1, y+1, WHITE, true, false, PAWN, x, y);
									moves.push_back(ta);
								}
						}
						else { //y is 7 cant take to the right. x still less than 6
							if(pos->the_board[x-1][y] == NULLCELL){
								Move ma(x-1, y, WHITE, false, false, PAWN, x, y);
								moves.push_back(ma);

								if(pos->the_board[x-2][y] == NULLCELL){
									Move mb(x-2, y, WHITE, false, false, PAWN, x, y);

									moves.push_back(mb);
								}
								moves.push_back(ma);
							}
							int enemy_s1 = pos->the_board[x-1][y-1];
							if(is_enemy_piece_type(enemy_s1) && !is_enemy_king(enemy_s1)){
								Move tb(x-1, y-1, WHITE, true, false, PAWN, x, y);
								moves.push_back(tb);
							}

						}
					}
			}
			else if(x == 1){ //  pawn one move from being on the back rank and promoting
				//a pawn promotion.
				//also breaks into subcases of y...
				int e;
				Move m_promote(x - 1, y, WHITE, false, true, PAWN, x, y);
				if(pos->the_board[x-1][y] == NULLCELL){
					moves.push_back(m_promote);
				}

				if(y > 0 && y < 7){
					Move mp2(x-1, y+1, WHITE, true, true, PAWN, x, y);
					e = pos->the_board[x-1][y+1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp2);
					}
					Move mp3(x-1, y-1, WHITE, true, true, PAWN, x, y);
					e = pos->the_board[x-1][y-1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp3);
					}


				}else if(y == 0){
					Move mp2(x-1, y+1, WHITE, true, true, PAWN, x, y);
					e = pos->the_board[x-1][y+1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp2);
					}
				}else{
					Move mp3(x-1, y-1, WHITE, true, true, PAWN, x, y);
					e = pos->the_board[x-1][y-1];
					if(is_enemy_piece_type(e) && !is_enemy_king(e)){
						moves.push_back(mp3);
					}
				}

			}
			else { //X is 0 white pawn on the back rank.
				//pawn on backrank that didn't choose to promote? or promoted to a pawn...?
			}
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
