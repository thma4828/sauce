#include "Board.h"


using namespace std;

Board::Board(){
  final_eval_black = 1.0;
  final_eval_white = 1.0;
}

bool Board::get_check_white(){
  //TODO determine if check is in the pos on whites king.
  return false;
}

bool Board::get_check_black(){
  //TODO...
  return false;
}

void Board::set_position(Position *p){
  position = p;
}

void Board::calc_final_eval(){
  //TODO: without looking at future positions just give naive evaluation...
}
float Board::get_wb_ratio(){
  return final_eval_white / (0.1 + final_eval_black);
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
