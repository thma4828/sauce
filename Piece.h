#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <vector>
#include "Position.h"
#include "Move.h"


using namespace std;
#define NONE 88
#define BLACK 1
#define WHITE 0
#define NULLCELL 3
#define PAWN 11
#define BISHOP 37
#define ROOK 87
#define KNIGHT 313
#define QUEEN 1717
#define KING 1337
#define WPAWN 56
#define BPAWN 76
#define WROOK 510
#define BROOK 710
#define WBISH 512
#define BBISH 712
#define WKING 51
#define BKING 71
#define WKNIGHT 511
#define BKNIGHT 711
#define BQUEEN 72
#define WQUEEN 52
#define START 5
#define EMPTY 6
#define T1 7
#define TEST_2 314556
#define TEST_3 0x78aa
#define TCHECK 0xabcd
#define TCASTLE 0x683
#define TPUZZLE1 0x7aab

class Piece
{
public:
	Piece(int); //just color
	Piece(); //null piece
	Piece(int, int); //null piece xy
	Piece(int, int, int, int, int, int); //x,y,c,p,xdiff,ydiff
	void set_xy(int, int);
	void set_color(int);
	int get_x();
	int get_y();
	int get_color();
	int get_color_set();
	int get_null_piece();
	int get_piece_type();
	int get_x_diff();
	int get_y_diff();
	void set_pos(Position*);
	vector<Move> get_moves();
	vector<Move> set_moves(bool); //flag for if you want to return all threats or all legal moves. 
	void clear_moves();
	int get_pos_status();
	bool is_enemy_piece_type(int);
	bool is_friendly_piece_type(int);
	bool is_enemy_king(int);
	void set_been_moved(bool);
	vector<Move>curr_moves;
	//TODO add in move calculation functionality again now that problem with class dep. resolved.


protected:
	int color;
	int is_color_set;
	int is_null_piece;
	int is_pos_set;
	int x;
	int y;
	int piece_type;
	int x_diff;
	int y_diff;
	bool been_moved;
	bool pinned;
	Position* pos;

};

#endif //PIECE_H
