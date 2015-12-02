#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn: public ChessPiece {
public:
	Pawn(char owner, char type, Game* game);
	~Pawn();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};

#endif
