#pragma once
#include "Piece.h"


using namespace std;

class Pawn :
    public Piece
{
public:
    using Piece::Piece;
    Pawn(); 
    Pawn(int, int, int, int, int, int);
    int get_piece_type(); //overloaded method
};



