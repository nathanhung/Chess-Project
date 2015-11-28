#include "chessPiece.h"

class Queen: public ChessPiece {
	~Queen();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
}
