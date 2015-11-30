#include "chessPiece.h"

Rook::Rook() {}

Rook::~Rook() {}

bool Rook::checkMove (int curRow, int curCol, int newRow, int newCol) {
	if (newRow !<= 7 || newRow !>= 0) return false;
        if (newCol !<= 7 || newCol !>= 0) return false; // check if new position is out of board
	
	for (int row = curRow; row <= 7; row++) {
		if (row == newRow && curCol == newCol) return true;
	}
	for (int row = curRow; row >= 0; row--) {
		if (row == newRow && curCol == newCol) return true;
	} 
	for (int col = curCol; col <= 7; col++) {
		if (col == newCol && curRow == newRow) return true;
	}
	for (int col = curCol; col >= 0; col--) {
		if (col == newCol && curRow == newRow) return true;
	}
	return false;
}
