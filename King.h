#ifndef KING_H
#define KING_H

#include "Piece.h"

using namespace std;

class King : 
	public Piece
{
public:
	using Piece::Piece;
	King();

	int get_piece_type();
	vector<Move> set_moves(bool); 

protected:
};

#endif //KING_H
