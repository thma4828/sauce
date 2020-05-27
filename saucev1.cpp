// saucev1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "Piece.h"
#include "Pawn.h"
#include "Position.h"
using namespace std;

void batch_test_1() {
    Pawn* p = new Pawn();

    assert(p->get_x() == -1 && p->get_y() == -1);
    assert(p->get_color() == NUL);
    p->set_color(WHITE);
    assert(p->get_color() == WHITE);
    p->set_xy(3, 5);
    assert(p->get_x() == 3 && p->get_y() == 5);


}


void batch_test_2() {
    Position pos_one = Position(T1); //T1 is for test position 1. 

    for (int i = 0; i < 8; i++) {
        Piece p1 = pos_one.the_board[1][i];
        Piece p2 = pos_one.the_board[6][i];

        assert(p1.get_color() == BLACK);
        assert(p1.get_piece_type() == PAWN);

        assert(p2.get_color() == WHITE);
        assert(p1.get_piece_type() == PAWN);

        assert(p1.get_x_diff() == 1);

    } 

    for (int k = 0; k < 8; k++) {
        Piece p3 = pos_one.the_board[0][k];
        Piece p4 = pos_one.the_board[5][k];
        Piece p5 = pos_one.the_board[3][k];

        assert(p3.get_null_piece() && p4.get_null_piece() && p5.get_null_piece());

    }
}

void ut_pawn_push_f1() {
    Position pos = Position(T1);
    Piece pawn_a7 = pos.the_board[1][0];

    vector<Move>moves = pawn_a7.get_moves(1, 0, &pos);
}

int main()
{
    cout << "Hello Sauce Engine v1.0" << endl;
    batch_test_1();
    cout << "batch test 1 success." << endl;
    batch_test_2();
    cout << "batch test 2 success." << endl;

    cout << "ALL TESTS PASSED" << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
