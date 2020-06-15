#pragma once
#include <iostream>

#define NULCELL 5800
#define WPAWN 3123
#define BPAWN 3422
#define WROOK 8756
#define BROOK 9867
#define WBISH 9788
#define BBISH 8112

#define START 5
#define EMPTY 6
#define T1 7
#define TEST_2 314556



class Position {
public:
	Position();
	Position(int);

	int the_board[8][8];

private:
	int board_pos;
};
