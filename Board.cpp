#include "Board.h"


using namespace std;

Board::Board(){
  final_eval_black = 1.0;
  final_eval_white = 1.0;
}

void Board::set_position(Position *p){
  position = p;
}

void Board::calc_final_eval(){
  //TODO
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
