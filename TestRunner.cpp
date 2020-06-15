#include "TestRunner.h"
#include <cassert>
#include "Piece.h"

using namespace std;


TestRunner::TestRunner() {
	//empty constructor, so lets just set to null position. 
    position = nullptr;
}

TestRunner::TestRunner(int pc) {
	position = new Position(pc);
}

TestRunner::TestRunner(Position* pos) {
	position = pos;
}



void TestRunner::batch_test_1() {
    Pawn* p = new Pawn();

    assert(p->get_x() == -1 && p->get_y() == -1);
    assert(p->get_color() == NUL);
    p->set_color(WHITE);
    assert(p->get_color() == WHITE);
    p->set_xy(3, 5);
    assert(p->get_x() == 3 && p->get_y() == 5);

}


void TestRunner::batch_test_2() {
    Position pos_one = Position(T1); //T1 is for test position 1. 

    for (int i = 0; i < 8; i++) { //only pawns with all possible moves for this test. 
        int p1 = pos_one.the_board[1][i];
        int p2 = pos_one.the_board[6][i];

        assert(p1 == BPAWN);
        assert(p2 == WPAWN);
        //now for each square we can create a class instance of that type on the appropriate square
        //then we can use the classes to calculate the lists of possible moves again. 
        Pawn pawn1 = Pawn(1, i, BLACK, PAWN, 1, 1);
        Pawn pawn2 = Pawn(6, i, WHITE, PAWN, 1, 1);
        pawn1.set_pos(&pos_one);
        pawn2.set_pos(&pos_one);

        assert(pawn1.get_pos_status() == true);
        assert(pawn1.get_null_piece() == false);
        assert(pawn1.get_color_set() == true);

        assert(pawn1.get_color() == BLACK);

        vector<Move>p1_moves = pawn1.set_moves();
        cout << "Black Pawn Moves" << endl;
        for (int m = 0; m < p1_moves.size(); m++) {
            Move mv = p1_moves[m];
            cout << "move # " << m << endl;
            cout << "starting coords: " << mv.x_start << "," << mv.y_start << endl;
            cout << "end coords: " << mv.x_end << "," << mv.y_end << endl;
            cout << "is take: " << mv.is_take << endl;
        }
        /*cout << "White Pawn Moves" << endl;
        vector<Move>p2_moves = pawn2.set_moves();
        for (int m = 0; m < p2_moves.size(); m++) {
            Move mp2 = p2_moves[m];
            cout << "move # " << m << endl;
            cout << "starting coords: " << mp2.x_start << "," << mp2.y_start << endl;
            cout << "end coords: " << mp2.x_end << "," << mp2.y_end << endl;
            cout << "is take: " << mp2.is_take << endl;
        }*/
    }

}

void TestRunner::run_all_batch_tests() {
    batch_test_1();
    batch_test_2();
    cout << "batch tests 1&2 passed." << endl;
}



void TestRunner::bishop_unit_test_02() {
    Bishop* b_01 = new Bishop(0, 1, BLACK, BISHOP, 1, 1); ///xdiff and ydiff now defunct params.. .. so 1...
    Bishop* b_06 = new Bishop(0, 6, BLACK, BISHOP, 1, 1);
    vector<Move> b1_moves = b_01->set_moves();
    vector<Move> b6_moves = b_06->set_moves();


    
}

void TestRunner::run_all_bishop_unit_tests() {
    cout << "Running all bishop unit tests. 01." << endl;
    bishop_unit_test_02();
    cout << "Bishop unit test passed. 02." << endl;
}

