#include "Knight.h"
#include "Piece.h"
#include "Move.h"
#include <iostream>

using namespace std;


Knight::Knight(){
  //
}

vector<Move> Knight::set_moves(){
  cout << "in knight: set moves." << endl;
  vector<Move>moves;
  if(is_color_set && is_pos_set && !is_null_piece){
    //x+1, y+2
    bool c1 = ((x+1) <= 7 && (y+2) <= 7);
    bool c2 = ((x+1) <= 7 && (y-2) >= 0);
    bool c3 = ((x-1) >= 0 && (y+2) <= 7);
    bool c4 = ((x-1) >= 0 && (y-2) >- 0);
    cout << "in knight: set moves." << endl;
    bool one_move = (c1 || c2 || c3 || c4);
    if(one_move){
    	cout << "------>knight has at least 1 move." << endl;
    }else{
    	cout << "------>knight has 0 moves. (usually an error)." << endl;
    }
    if(c1){
      cout << "------->move x+1, y+2 is supposed to be in bounds" << endl;
      int square12 = pos->the_board[x+1][y+2];
      if(square12 == NULLCELL){
	cout << "------>knight move to empty square. " << endl;
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
  curr_moves = moves;
  return moves;
}

int Knight::get_piece_type(){
  return KNIGHT;
}
