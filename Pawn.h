#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"


using namespace std;

class Pawn :
    public Piece
{
public:
    using Piece::Piece;
    Pawn(); 
    
    int get_piece_type(); //overloaded method
    vector<Move> set_moves(bool); 

protected:
    //inherited members of piece are present. 
};


#endif //PAWN_H
