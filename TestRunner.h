#pragma once
#include "Position.h"
#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
using namespace std;
class TestRunner
{
public:
	TestRunner();
	TestRunner(Position*);
	TestRunner(int);
	void run_all_batch_tests();
	void run_all_bishop_unit_tests();
	

private:
	Position* position;
	void batch_test_1();
	void batch_test_2();
	
	void bishop_unit_test_02();
};

