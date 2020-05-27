#include "Pawn.h"
#include <iostream>
#include <vector>

using namespace std;

Pawn::Pawn() {
	x_diff = 1;
	y_diff = 1;
}

Pawn::Pawn(int a, int b, int c, int type, int dx, int dy) {
	x = a;
	y = b;
	color = c;
	piece_type = type;
	x_diff = dx;
	y_diff = dy;
	
	is_color_set = true;
	is_null_piece = false;
}


int Pawn::get_piece_type() {
	return PAWN;
}
