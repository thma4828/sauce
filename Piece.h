#pragma once
#include <iostream>
#include <vector>
#include "Position.h"
#include "Move.h"


using namespace std;
#define WHITE -1
#define BLACK 1
#define NUL 3
#define PAWN 11
#define BISHOP 37
#define ROOK 87
#define KNIGHT 313
#define QUEEN 1717
#define KING 1337
#define WPAWN 3123
#define BPAWN 3422
#define WROOK 8756
#define BROOK 9867
#define WBISH 9788
#define BBISH 8112
#define WKING 7655
#define BKING 1232

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
	vector<Move> set_moves();
	void clear_moves();
	int get_pos_status();
	int is_enemy_piece_type(int);
	int is_enemy_king(int);
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
	Position* pos;
	
};

