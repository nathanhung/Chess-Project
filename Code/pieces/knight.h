#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight: public ChessPiece {
public:
	Knight(char owner, char type, Game* game);
	~Knight();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};
#endif
