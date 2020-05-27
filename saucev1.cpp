// saucev1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "Piece.h"
#include "Pawn.h"
#include "Position.h"

#define WPAWN 31
#define BPAWN 34
#define NULCELL 58

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
        int p1 = pos_one.the_board[1][i];
        int p2 = pos_one.the_board[6][i];
        assert(p1 == BPAWN && p2 == WPAWN);
        //now for each square we can create a class instance of that type on the appropriate square
        //then we can use the classes to calculate the lists of possible moves again. 
        Pawn pawn1 = Pawn(1, i, BLACK, PAWN, 1, 1);
        pawn1.set_pos(&pos_one);

    } 

}


int main()
{
    cout << "Hello Sauce Engine v1.0" << endl;
    batch_test_1();
    cout << "batch test 1 success." << endl;
    batch_test_2();
    cout << "batch test 2 success." << endl;
    //I need to have some sort of API where each piece can view the entire position
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
