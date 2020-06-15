#pragma once
#include "Position.h"
#include "Piece.h"
#include <vector>
class Board //this interface will taken a position, get all the moves of both sides and organize them
{
public:
	Board();
private:
	Position* position;
	//needs to:
		//go through the position and create a piece class for each piece it finds (can be 1 at a time)
		//then get the moves for each piece and store in a big array of moves.
	vector<Move>black_moves;
	vector<Move>white_moves;

	double black_piece_value;
	double white_piece_value;
	double black_threat_value;
	double white_threat_value;
	double black_structure_value;
	double white_structure_value;

	double final_eval_white;
	double final_eval_black;
	//TODO add score mechanism for threats and piece value. 
};

