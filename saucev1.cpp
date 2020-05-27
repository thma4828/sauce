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



    Position pos_one = Position(T1);

    Piece p1 = pos_one.the_board[1][1];
    Piece p2 = pos_one.the_board[6][1];
}

int main()
{
    cout << "Hello Sauce Engine v1.0" << endl;
    batch_test_1();
    

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
