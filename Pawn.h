#pragma once
#include "Piece.h"
using namespace std;

class Pawn :
    public Piece
{
    using Piece::Piece; //allows me to overload the piece constructors I have for making a pawn. 
   
public:
    Pawn();
    int get_piece_type();
    Move* get_moves(int, int);
};

