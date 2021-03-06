#ifndef BOARD_H
#define BOARD_H
#include "Position.h"
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h" 
#include "Square.h"
#include <vector>

using namespace std;

class Board //this interface will taken a position, get all the moves of both sides and organize them
{
public:
	Board();
	void set_position(Position *);
	Position *get_position();
	void calc_final_eval();
	float get_wb_ratio();
	float get_black();
	float get_white();
	bool get_check_white();
	bool get_check_black();
	void set_color(int);
	bool is_white();
	bool is_black();
	vector<Square>get_threat_squares(int); 
private:
	Position* position;
	//needs to:
		//go through the position and create a piece class for each piece it finds (can be 1 at a time)
		//then get the moves for each piece and store in a big array of moves.
	vector<Move>black_moves;
	vector<Move>white_moves;
	vector<Square>white_threat_squares;
	vector<Square>black_threat_squares; 
	float black_piece_value;
	float white_piece_value;
	float black_threat_value;
	float white_threat_value;
	float black_structure_value;
	float white_structure_value;

	float final_eval_white;
	float final_eval_black;

	int color;
	//TODO add score mechanism for threats and piece value.
};
#endif //BOARD_H
