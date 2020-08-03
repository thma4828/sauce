# sauce
chess engine in c++ with std=c++11.

Main.cpp 
  -create a generator.h class object and set it to have an initial board position. I use test position T1 which has a few pieces for white and black near the center of the board. 
  -let the generator build out the tree of chess moves to a specific depth with build_tree().
  -many print statements which are for debugging purposes slow down execution. these will be removed with a version in the future where you can suppress the prints. 
  -as tree is built each position (internal to the node) uses the Board.h interface to naively evaluate the position based on a count of piece values. 
  -then this leads to the tree evaluation algorithm / line calculator which is the crucial part of the engine, still thinking about this part. 
  
TODO: will explain project in detail. 
