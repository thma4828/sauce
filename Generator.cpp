#include "Generator.h"


Generator::Generator(){
  //
}

Generator::Generator(Position *start, int start_color){
  Node *root = new Node(nullptr, start_color, 0.1, 0.1);
  Board *root_board = new Board();
  root_board->set_position(start);
  root->set_board(root_board);
  //now node needs to use the board to get
  //the default (naive) evaluation on the position.
  root->assign_board_val();//node now has naive evaluation.
  move_tree = new Tree(root);
}
