#include "Knight.h"
#include "Piece.h"
#include "Move.h"
#include <iostream>

using namespace std;


Knight::Knight(){
  //
}

vector<Move> Knight::set_moves(){
  cout << "in knight set moves." << endl;
  vector<Move>moves;
  if(is_color_set && is_pos_set && !is_null_piece){
    //x+1, y+2
    bool c1 = ((x+1) <= 7 && (y+2) <= 7);
    if(c1){
      cout << "move x+1, y+2 is supposed to be in bounds" << endl;
      int square12 = pos->the_board[x+1][y+2];
      if(square12 == NULLCELL){
        Move m1(x+1, y+2, color, false, false, KNIGHT, x, y);
        moves.push_back(m1);
      }else if(is_enemy_piece_type(square12) && !is_enemy_king(square12)){
        Move t1(x+1, y+2, color, true, false, KNIGHT, x, y);
        moves.push_back(t1);
      }else if(is_enemy_king(square12)){
          //unanswered check on the board...
      }
    }

  }else{
    cout << "knight piece not initilized." << endl;
  }
  return moves;
}

int Knight::get_piece_type(){
  return KNIGHT;
}
