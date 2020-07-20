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
    //TODO c5-c8
    cout << "in knight: set moves." << endl;
    bool one_move = (c1 || c2 || c3 || c4);
    if(one_move){
    	cout << "------>knight has at least 1 move." << endl;
    }else{
    	cout << "------>knight has 0 moves. (usually an error)." << endl;
    }
    if(c1){
      cout << "------->move x+1, y+2 is supposed to be in bounds" << endl;
      int squarec1 = pos->the_board[x+1][y+2];
      if(squarec1 == NULLCELL){
	cout << "------>knight move to empty square. " << endl;
        Move m1(x+1, y+2, color, false, false, KNIGHT, x, y);
        moves.push_back(m1);
      }else if(is_enemy_piece_type(squarec1)){
	cout << "------>knight takes on non-empty square. " << endl;
        Move t1(x+1, y+2, color, true, false, KNIGHT, x, y);
        moves.push_back(t1);
      }else if(!is_enemy_piece_type(squarec1) && !is_enemy_king(squarec1)){
      	cout << "------>knight obstructed by friendly piece." << endl;
      }else if(is_enemy_king(squarec1)){
      	//check on the board. 
      }
    }
    if(c2){
    	cout << "------>move x+1, y-2 is supposed to be in bounds" << endl;
	int squarec2 = pos->the_board[x+1][y-2];
	if(squarec2 == NULLCELL){
		cout << "------>knight move to empty square. " << endl;
		Move m2(x+1, y-2, color, false, false, KNIGHT, x, y);
		moves.push_back(m2);
	}else if(is_enemy_piece_type(squarec2)){
		cout << "------>knight takes on non-empty square. " << endl;
		Move t2(x+1, y-2, color, true, false, KNIGHT, x, y);
		moves.push_back(t2);
	}else if(!is_enemy_piece_type(squarec2) && !is_enemy_king(squarec2)){
		cout << "------>knight obstructed by friendly piece." << endl;
	}else if(is_enemy_king(squarec2)){
		//unanswered check...
	}
    }
    if(c3){
    	cout << "------>move x-1, y+2 supposed to be in bounds." << endl;
	int squarec3 = pos->the_board[x-1][y+2];
	if(squarec3 == NULLCELL){
		cout << "------>knight move to empty square. " << endl;
		Move m3(x-1, y+2, color, false, false, KNIGHT, x, y);
		moves.push_back(m3);

	}else if(is_enemy_piece_type(squarec3)){
		cout << "------>knight takes on non-empty square. " << endl;
		Move t3(x-1, y+2, color, true, false, KNIGHT, x, y);
		moves.push_back(t3);
	}else if(!is_enemy_piece_type(squarec3) && !is_enemy_king(squarec3)){
		cout << "------>knight obstructed by its own piece. " << endl;
	}else if(is_enemy_king(squarec3)){
		//check. 
	}
    }
    if(c4){
    	cout << "------>move x-1, y-2 supposed to be in bounds." << endl;
	int squarec4 = pos->the_board[x-1][y-2];
	if(squarec4 == NULLCELL){
		cout << "------>knight move to empty square. " << endl;
		Move m4(x-1, y-2, color, false, false, KNIGHT, x, y);
		moves.push_back(m4);
	}else if(is_enemy_piece_type(squarec4)){
		cout << "------>knight takes on non-empty square. " << endl;
		Move t4(x-1, y-2, color, true, false, KNIGHT, x, y);
		moves.push_back(t4);
	}else if(!is_enemy_king(squarec4) && !is_enemy_king(squarec4)){
		cout << "------>knight obstructed by its own piece. " << endl;
	}else if(is_enemy_king(squarec4)){
		//check
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
