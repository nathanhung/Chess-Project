#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King: public ChessPiece {
	King();
	~King();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};

#endif
