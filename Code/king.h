#include "ChessPiece.h"

class King: public ChessPiece {
	~King();
	bool checkMove(int row, int col);
}



