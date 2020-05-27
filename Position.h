#pragma once
#include <iostream>
#include "Piece.h"
#include "Pawn.h"

#define START 5
#define EMPTY 6
#define T1 7


class Position {
public:
	Position(int);

	Piece A[8][8];

private:
	int board_pos;
};