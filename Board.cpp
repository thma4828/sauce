#include "Board.h"


#define BLACK 1
#define WHITE 0
#define NULLCELL 3
#define PAWN 11
#define BISHOP 37
#define ROOK 87
#define KNIGHT 313
#define QUEEN 1717
#define KING 1337
#define WPAWN 3123
#define BQUEEN 171710
#define WQUEEN 171720
#define BPAWN 3422
#define WROOK 8756
#define BROOK 9867
#define WBISH 9788
#define BBISH 8112
#define WKING 7655
#define BKING 1232
#define WKNIGHT 7171
#define BKNIGHT 8712

using namespace std;

Board::Board(){
  final_eval_black = 1.0;
  final_eval_white = 1.0;
}

void Board::set_color(int c){
  color = c;
}

bool Board::get_check_white(){
  //TODO determine if check is in the pos on whites king.
  return false;
}

bool Board::get_check_black(){
  //TODO...
  return false;
}

bool Board::is_white(){
  if(color == WHITE)
    return true;
  else
    return false;
}
bool Board::is_black(){
  return !is_white();
}

void Board::set_position(Position *p){
  position = p;
}

void Board::calc_final_eval(){
  //TODO: without looking at future positions just give naive evaluation...
  //start with adding up piece totals...
  //if check on the board worth something.
  //if checkmate worth some const INF

  final_eval_black = 1.0;
  final_eval_white = 1.0;

  for(int x=0; x<8; x++){
    for(int y=0; y<8; y++){
      int piece_code = position->the_board[x][y];
      if(piece_code == WPAWN){
        final_eval_white += 1.0;
      }
      if(piece_code == BPAWN){
        final_eval_black += 1.0;
      }
      if(piece_code == WKNIGHT){
        final_eval_white += 3.0;
      }
      if(piece_code == BKNIGHT){
        final_eval_black += 3.0;
      }
      if(piece_code == WBISH){
        final_eval_white += 3.0;
      }
      if(piece_code == BBISH){
        final_eval_black += 3.0;
      }
      if(piece_code == WROOK){
        final_eval_white += 5.0;
      }
      if(piece_code == BROOK){
        final_eval_black += 5.0;
      }
      if(piece_code == WQUEEN){
        final_eval_white += 9.0;
      }
      if(piece_code == BQUEEN){
        final_eval_black += 9.0;
      }

    }
  }
}
float Board::get_wb_ratio(){
  return (0.1 + final_eval_white) / (0.1 + final_eval_black);
}
float Board::get_black(){
  return final_eval_black;
}
float Board::get_white(){
  return final_eval_white;
}

Position *Board::get_position(){
  return position;
}
