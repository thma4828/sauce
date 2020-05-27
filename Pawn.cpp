#include "Pawn.h"
#include <iostream>

using namespace std;

Pawn::Pawn() {
	//
}

Move* Pawn::get_moves(int x, int y) {
	if (is_color_set) {
		if (color == BLACK) { //black pawn
			if (x < 7) {
				//really we need to pass in a board to each class to figure this out! 
			}
		}
		else { //white pawn
		
		}
	}
	return nullptr;
}

int Pawn::get_piece_type() {
	return PAWN;
}

