#ifndef BOARD_H
#define BOARD_H
#include "Position.h"
#include "Move.h"
#include "Piece.h"
#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h" 
#include "Square.h"
#include <vector>

using namespace std;

class Board //this interface will taken a position, get all the moves of both sides and organize them
{
public:
	Board();
	~Board();
	void set_position(Position *);
	void set_position_ep_squares(vector<vector<int>>, int); //int is WB 
	vector<vector<int>> get_position_ep_squares(int); 
	Position *get_position();
	void calc_final_eval();
	double get_wb_ratio();
	double get_black();
	double get_white();
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

	double pos_eval_white;
	double pos_eval_black;

	double mat_eval_white;
	double mat_eval_black;

	int color;
	//TODO add score mechanism for threats and piece value.
};
#endif //BOARD_H
