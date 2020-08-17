#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include "Move.h"
#include <vector>

using namespace std;

class Knight :
    public Piece
{
public:
  using Piece::Piece;
  Knight();
  
  int get_piece_type();
  vector<Move> set_moves(bool);

protected:
  //
};


#endif //KNIGHT_H
