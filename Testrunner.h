#ifndef TESTRUNNER_H
#define TESTRUNNER_H
#include "Position.h"
#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
using namespace std;


class Testrunner
{
public:
	Testrunner();
	Testrunner(Position*);
	Testrunner(int);
	void run_all_batch_tests();
	void run_all_bishop_unit_tests();
	void pawn_t();


private:
	Position* position;
	void batch_test_1();
	void batch_test_2();

	void bishop_unit_test_02();
};
#endif //TESTRUNNER_H
