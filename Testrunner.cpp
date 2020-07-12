#include "Testrunner.h"
#include <cassert>
#include "Piece.h"

using namespace std;


Testrunner::Testrunner() {
	//empty constructor, so lets just set to null position.
    position = nullptr;
}

Testrunner::Testrunner(int pc) {
	position = new Position(pc);
}

Testrunner::Testrunner(Position* pos) {
	position = pos;
}

void Testrunner::knight_01(){
  cout << "In knight tests." << endl;
  position = new Position(TEST_2);
  //white knight on x=2, y=3
  //black knight on x=3, y=4
  //white pawns on x=6 rank
  //black pawns on x=1 rank
  int wk = position->the_board[2][3];
  int bk = position->the_board[3][4];
  assert(wk == WKNIGHT);
  assert(bk == BKNIGHT);
  Knight *wk1 = new Knight(2, 3, WHITE, KNIGHT, 2, 3);
  Knight *bk1 = new Knight(3, 4, BLACK, KNIGHT, 2, 3);
  wk1->set_pos(position);
  bk1->set_pos(position);

  wk1->set_moves();
  vector<Move>wk1_moves = wk1->get_moves();
  assert(wk1_moves.size() > 0);
}

void Testrunner::simple_pawn_lines() {
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
        assert(p1_moves.size() > 0);
        for (int m = 0; m < p1_moves.size(); m++) {
            Move mv = p1_moves[m];
            cout << "move # " << m << endl;
            cout << "starting coords: " << mv.x_start << "," << mv.y_start << endl;
            cout << "end coords: " << mv.x_end << "," << mv.y_end << endl;
            cout << "is take: " << mv.is_take << endl;
        }
        assert(pawn2.get_color() == WHITE);
        assert(pawn2.get_pos_status() == true);
        assert(pawn2.get_color_set() == true);
        assert(pawn2.get_null_piece() == false);
        cout << "White Pawn Moves" << endl;
        vector<Move>p2_moves = pawn2.set_moves();
        assert(p2_moves.size() > 0);
        for (int m = 0; m < p2_moves.size(); m++) {
            Move mp2 = p2_moves[m];
            cout << "move # " << m << endl;
            cout << "starting coords: " << mp2.x_start << "," << mp2.y_start << endl;
            cout << "end coords: " << mp2.x_end << "," << mp2.y_end << endl;
            cout << "is take: " << mp2.is_take << endl;
        }
    }

}

void Testrunner::bishop_unit_test_01() {
    Position *pos_2 = new Position(TEST_3);

    assert(pos_2->the_board[0][0] == BBISH);
    assert(pos_2->the_board[7][7] == WBISH);

    Bishop* b_01 = new Bishop(0, 0, BLACK, BISHOP, 1, 1); ///xdiff and ydiff now defunct params.. .. so 1...
    Bishop* b_06 = new Bishop(7, 7, WHITE, BISHOP, 1, 1);

    b_01->set_pos(pos_2);
    b_06->set_pos(pos_2);


    vector<Move> b1_moves = b_01->set_moves();
    vector<Move> b6_moves = b_06->set_moves();

}

void Testrunner::run_all_batch_tests() {

    simple_pawn_lines();
    cout << "simple pawn lines passed." << endl;
    knight_01();
    cout << "knight test 01 passed." << endl;
    bishop_unit_test_01();
    cout << "bishop unit test 01 passed." << endl;
}
