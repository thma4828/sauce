#ifndef POSITION_H
#define POSITION_H
#include <iostream>

class Position {
public:
	Position();
	Position(int);

	int the_board[8][8];

private:
	int board_pos;
};

#endif //POSITION_H
