#pragma once
#include <iostream>
#include <vector>

using namespace std;
#define WHITE -1
#define BLACK 1
#define NUL 3
#define PAWN 11

struct Move {
	int x;
	int y;
	int color;
	int is_take;
};
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
	vector<Move> get_moves(int, int, void*);

	
protected:
	int color;
	int is_color_set;
	int is_null_piece;
	int x;
	int y;
	int piece_type;
	int x_diff;
	int y_diff;
	vector<Move>moves;
};

