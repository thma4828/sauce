#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

using namespace std;

class Queen : 
	public Piece
{
public:
	using Piece::Piece;
	Queen();

	int get_piece_type();
	vector<Move> set_moves(bool);

protected:
	//inherited members

};


#endif //QUEEN_H
