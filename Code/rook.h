#include "chessPiece.h"

class Rook: public ChessPiece {
	~Rook();
        bool checkMove(int curRow, int curCol, int newRow, int newCol);	
}
