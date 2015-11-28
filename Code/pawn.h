#include "chessPiece.h"

class Pawn: public ChessPiece {
	~Pawn();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
}

