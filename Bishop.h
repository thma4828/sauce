#pragma once
#include "Piece.h"

using namespace std;
class Bishop : 
	public Piece
{
public:

	using Piece::Piece;
	Bishop();
	int get_piece_type();
	vector<Move> set_moves();
protected:
};

