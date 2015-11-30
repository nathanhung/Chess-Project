#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop: public ChessPiece {
	Bishop(char owner, char type, Game* game);
	~Bishop();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};
#endif
