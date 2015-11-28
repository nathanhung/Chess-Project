#include "chessPiece.h"

class Bishop: public ChessPiece {
	~Bishop();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
}
