#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class Knight: public ChessPiece {
	Knight(char owner, char type, Game* game);
	~Knight();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};
#endif
