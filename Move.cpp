#include "Move.h"


Move::Move(int xe, int ye, int cc, int ist, int isp, int pt, int xs, int ys) {
	x_end = xe;
	y_end = ye;
	x_start = xs;
	y_start = ys;
	color = cc;
	is_take = ist;
	is_promote = isp;
	piece_type = pt;
}