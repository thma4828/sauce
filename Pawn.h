#pragma once
#include "Piece.h"


using namespace std;

class Pawn :
    public Piece
{
public:
    using Piece::Piece;
    Pawn(); 
    
    int get_piece_type(); //overloaded method
    vector<Move> set_moves();

protected:
    //inherited members of piece are present. 
};



