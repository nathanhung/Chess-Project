#include "chessPiece.h"

class Knight: public ChessPiece {
	~Knight();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
}
