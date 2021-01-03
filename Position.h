#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include <vector>

using namespace std; 
class Position {
public:
	Position();
	Position(int);
	~Position();
	void read_board_file(std::string); 

	int the_board[8][8];
	vector<vector<int>>ep_squares_white;
	vector<vector<int>>ep_squares_black; 

private:
	int board_pos;
};

#endif //POSITION_H
