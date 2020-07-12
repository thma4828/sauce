#ifndef TESTRUNNER_H
#define TESTRUNNER_H
#include "Position.h"
#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
using namespace std;


class Testrunner
{
public:
	Testrunner();
	Testrunner(Position*);
	Testrunner(int);
	void run_all_batch_tests();




private:
	Position* position;

	void simple_pawn_lines();
	void knight_01();
	void bishop_unit_test_01();
};
#endif //TESTRUNNER_H
