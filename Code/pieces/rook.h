#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"
class Game;
class Rook: public ChessPiece {
public:
	Rook(char owner, char type, Game* game); 
	~Rook();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};
#endif
