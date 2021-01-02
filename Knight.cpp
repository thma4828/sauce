#include "Knight.h"
#include "Piece.h"
#include "Move.h"
#include <iostream>

using namespace std;


Knight::Knight(){
  //
}

vector<Move> Knight::set_moves(bool threats){
  //cout << "in knight: set moves." << endl;
  vector<Move>moves;
  vector<Move>threatvec;
  if(is_color_set && is_pos_set && !is_null_piece){
    //x+1, y+2
    bool c1 = ((x+1) <= 7 && (y+2) <= 7);
    bool c2 = ((x+1) <= 7 && (y-2) >= 0);
    bool c3 = ((x-1) >= 0 && (y+2) <= 7);
    bool c4 = ((x-1) >= 0 && (y-2) >= 0);
    bool c5 = ((x+2) <= 7 && (y+1) <= 7);
    bool c6 = ((x+2) <= 7 && (y-1) >= 0);
    bool c7 = ((x-2) >= 0 && (y+1) <= 7);
    bool c8 = ((x-2) >= 0 && (y-1) >= 0);
    //TODO c5-c8
    //cout << "in knight: set moves: color/pos are set." << endl;
    //bool one_move = (c1 || c2 || c3 || c4
//		    || c5 || c6 || c7 || c8);
   // if(one_move){
   // 	cout << "------>knight has at least 1 move." << endl;
   // }else{
   // 	cout << "------>knight has 0 moves. (usually an error)." << endl;
   // }
    if(c1){
     // cout << "------->move x+1, y+2 is supposed to be in bounds" << endl;
      int squarec1 = pos->the_board[x+1][y+2];
      if(squarec1 == NULLCELL){
//	cout << "------>knight move to empty square. " << endl;
        Move m1(x+1, y+2, color, false, false, KNIGHT, x, y, false, false);
	threatvec.push_back(m1);
        moves.push_back(m1);
      }else if(is_enemy_piece_type(squarec1)){
//	cout << "------>knight takes on non-empty square. " << endl;
        Move t1(x+1, y+2, color, true, false, KNIGHT, x, y, false, false);
        moves.push_back(t1);
	threatvec.push_back(t1); 
      }else if(!is_enemy_piece_type(squarec1)){
  //    	cout << "------>knight obstructed by friendly piece." << endl;
	Move t2(x+1, y+1, color, true, false, KNIGHT, x, y, false, false);
	threatvec.push_back(t2); 
      }else{
    //  	cout << "------>move escaped being captured by logical cases...." << endl;

      }
    }
   // cout << "------>knight analyzed c1 moved to c2." << endl;
    if(c2){
    //	cout << "------>move x+1, y-2 is supposed to be in bounds" << endl;
	int squarec2 = pos->the_board[x+1][y-2];
	if(squarec2 == NULLCELL){
//		cout << "------>knight move to empty square. " << endl;
		Move m2(x+1, y-2, color, false, false, KNIGHT, x, y, false, false);
		threatvec.push_back(m2); 
		moves.push_back(m2);
	}else if(is_enemy_piece_type(squarec2)){
//		cout << "------>knight takes on non-empty square. " << endl;
		Move t2(x+1, y-2, color, true, false, KNIGHT, x, y, false, false);
		moves.push_back(t2);
		threatvec.push_back(t2); 
	}else if(!is_enemy_piece_type(squarec2)){
//		cout << "------>knight obstructed by friendly piece." << endl;
		Move t2(x+1, y-2, color, true, false, KNIGHT, x,  y, false, false);
		threatvec.push_back(t2); 
	}
    }
  //  cout << "------>knight analyzed c2 now moving to c3." << endl;
    if(c3){
    //	cout << "------>move x-1, y+2 supposed to be in bounds." << endl;
	int squarec3 = pos->the_board[x-1][y+2];
	if(squarec3 == NULLCELL){
//		cout << "------>knight move to empty square. " << endl;
		Move m3(x-1, y+2, color, false, false, KNIGHT, x, y, false, false);
		moves.push_back(m3);
		threatvec.push_back(m3);

	}else if(is_enemy_piece_type(squarec3)){
//		cout << "------>knight takes on non-empty square. " << endl;
		Move t3(x-1, y+2, color, true, false, KNIGHT, x, y, false, false);
		moves.push_back(t3);
		threatvec.push_back(t3); 
	}else if(!is_enemy_piece_type(squarec3)){
//		cout << "------>knight obstructed by its own piece. " << endl;
		Move t3(x-1, y+2, color, true, false, KNIGHT, x, y, false, false);
		threatvec.push_back(t3); 
	}
    }
  //  cout << "------>knight analyzed c3 moving to c4." << endl;
    if(c4){
    //	cout << "------>move x-1, y-2 supposed to be in bounds." << endl;
	int squarec4 = pos->the_board[x-1][y-2];
	if(squarec4 == NULLCELL){
//		cout << "------>knight move to empty square. " << endl;
		Move m4(x-1, y-2, color, false, false, KNIGHT, x, y, false, false);
		moves.push_back(m4);
		threatvec.push_back(m4);
	}else if(is_enemy_piece_type(squarec4)){
//		cout << "------>knight takes on non-empty square. " << endl;
		Move t4(x-1, y-2, color, true, false, KNIGHT, x, y, false, false);
		moves.push_back(t4);
		threatvec.push_back(t4); 
	}else if(!is_enemy_piece_type(squarec4)){
//		cout << "------>knight obstructed by its own piece. " << endl;
		Move t4(x-1, y-2, color, true, false, KNIGHT, x, y, false, false); 
		threatvec.push_back(t4); 
	}
    }
  //  cout << "------>knight analyzed c4 moving to c5 (TODO)" << endl;
    if(c5){
    //	cout << "------>move x+2, y+1 in bounds." << endl;
	int squarec5 = pos->the_board[x+2][y+1];
	if(squarec5 == NULLCELL){
//		cout << "------>knight moves to empty square." << endl;

		Move m5(x+2, y+1, color, false, false, KNIGHT, x, y, false, false);
		moves.push_back(m5);
		threatvec.push_back(m5);
	}else if(is_enemy_piece_type(squarec5)){		Move t5(x+2, y+1, color, true, false, KNIGHT, x, y, false, false);
		moves.push_back(t5);
		threatvec.push_back(t5); 
	}else if(!is_enemy_piece_type(squarec5)){
		
//		cout << "knight is obstructed by friendly piece." << endl;
		Move t6(x+2, y+1, color, true, false, KNIGHT, x, y, false, false);
		threatvec.push_back(t6);
	}
    }
    if(c6){
  //  	cout << "------>move x+2, y-1 in bounds." << endl;
	int squarec6 = pos->the_board[x+2][y-1];
	if(squarec6 == NULLCELL){
//		cout << "------>knight moves to empty square." << endl;
		Move m6(x+2, y-1, color, false, false, KNIGHT, x, y, false, false);
		moves.push_back(m6);
		threatvec.push_back(m6);
	}else if(is_enemy_piece_type(squarec6)){
//		cout << "------>knight takes enemy piece." << endl;
		Move t6(x+2, y-1, color, true, false, KNIGHT, x, y, false, false);
		moves.push_back(t6);
		threatvec.push_back(t6); 
	}else if(!is_enemy_piece_type(squarec6)){
	
//		cout << "------>knight obstructed by friendly piece." << endl;
		Move t6(x+2, y-1, color, true, false, KNIGHT, x, y, false, false);
		threatvec.push_back(t6);
	}

    }
    if(c7){
//	cout << "------>move x-2,y+1 supposed to be in bounds." << endl;
    	int squarec7 = pos->the_board[x-2][y+1];
	if(squarec7 == NULLCELL){
//		cout << "------>knight moves to empty square." << endl;
		Move m7(x-2, y+1, color, false, false, KNIGHT, x, y, false, false);
		moves.push_back(m7);
		threatvec.push_back(m7);
	}else if(is_enemy_piece_type(squarec7)){
//		cout << "------>knight takes enemy piece." << endl;
		Move t7(x-2, y+1, color, true, false, KNIGHT, x, y, false, false);
		moves.push_back(t7);
		threatvec.push_back(t7);
	}else if(!is_enemy_piece_type(squarec7)){
		
//		cout << "------>knight obstructed by friendly piece." << endl;
		Move t7(x-2, y+1, color, true, false, KNIGHT, x, y, false, false);
		threatvec.push_back(t7);
	}

    }
    if(c8){
//	cout << "------>move x-2,y-1 supposed to be in bounds." << endl;
	int squarec8 = pos->the_board[x-2][y-1];
	if(squarec8 == NULLCELL){
//		cout << "------>knight moves to empty square." << endl;
		Move m8(x-2, y-1, color, false, false, KNIGHT, x , y, false, false);
		moves.push_back(m8);
		threatvec.push_back(m8);
	
	}else if(is_enemy_piece_type(squarec8)){
//		cout << "------>knight takes enemy piece." << endl;
		Move t8(x-2, y-1, color, true, false, KNIGHT, x, y, false, false);
		moves.push_back(t8);
		threatvec.push_back(t8); 
	
	}else if(!is_enemy_piece_type(squarec8)){
		
//		cout << "------>knight obstructed by friendly piece." << endl;
		Move t8(x-2, y-1, color, true, false, KNIGHT, x, y, false, false); 
		threatvec.push_back(t8); 
	}
    
    }

  }else{
  //  cout << "knight piece not initilized." << endl;
  }
  curr_moves = moves;
  if(threats)
	  return threatvec;
  return moves;
}

int Knight::get_piece_type(){
  return KNIGHT;
}
