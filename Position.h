#pragma once
#include <iostream>
#include "Piece.h"


#define START 5
#define EMPTY 6
#define T1 7


class Position {
public:
	Position();
	Position(int);

	Piece the_board[8][8];

private:
	int board_pos;
};