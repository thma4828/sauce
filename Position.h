#pragma once
#include <iostream>


#define START 5
#define EMPTY 6
#define T1 7


class Position {
public:
	Position();
	Position(int);

	int the_board[8][8];

private:
	int board_pos;
};
