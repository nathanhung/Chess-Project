#ifndef QUEEN_H
#define QUEEN_H

#include "../chesspiece.h"

class Queen: public ChessPiece {
	Queen();
	~Queen();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};

#endif
