#ifndef MOVE_H
#define MOVE_H
#include <string>
using namespace std;

class Move
{
public:
	int x_end;
	int y_end;
	int x_start;
	int y_start;
	int color;
	int is_take;
	int is_promote;
	int piece_type;

	//int x_end, int y_end, int color, int is_take, int is_promote, int piece_type, int x_start, int y_start
	Move(int, int, int, int, int, int, int, int);
	string get_move_string();
};
#endif //MOVE_H
