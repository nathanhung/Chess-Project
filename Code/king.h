#include "ChessPiece.h"

class King: public ChessPiece {
	~King();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
}

