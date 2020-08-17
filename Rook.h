#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

using namespace std;

class Rook : 
	public Piece
{
public:
	using Piece::Piece;
	Rook();
	int get_piece_type();
	vector<Move> set_moves(bool);
};

#endif //ROOK_H
