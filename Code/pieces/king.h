#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King: public ChessPiece {
	King(char owner, char type, Game* game); 
	~King();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};

#endif
