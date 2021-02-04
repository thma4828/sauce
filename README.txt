HOW TO COMPILE ENGINE VERSION 1

g++ -O3 -std=c++11 Main2.cpp Tree.cpp Node.cpp Valindex.cpp Piece.cpp Pawn.cpp Knight.cpp Bishop.cpp Move.cpp Generator.cpp Position.cpp Board.cpp Rook.cpp Queen.cpp King.cpp Square.cpp -o salsa.engine.2


HOW TO USE VERSION 1

./salsa.engine.2 4 5 1 puzzle_01.txt

(argument list is, build depth (n+1 is true build depth), eval depth (n) 
1 for black 0 for white, name of puzzle file is an 8x8 board with black at the 
top with pieces coded as they are defined in my Piece.h file.

NOTE: if you try to build to too great of a depth it will be killed as you run
out of ram, 

NOTE: on some rare build depths and positions it is possible to get a seg fault if you get a seg fault try changing the build depth. this issue I am working to
fix.  
