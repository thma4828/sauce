#pragma once
#include "Piece.h"
#include "Position.h"

using namespace std;

class Pawn :
    public Piece
{
    using Piece::Piece; //allows me to overload the piece constructors I have for making a pawn. 
   
public:
    Pawn(); 
    int get_piece_type(); //overloaded method
    vector<Move> get_moves(int, int, Position* p); //overloaded method
};

