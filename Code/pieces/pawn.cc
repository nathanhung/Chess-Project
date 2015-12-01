#include "pawn.h"

Pawn::Pawn(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

Pawn::~Pawn() {}

bool Pawn::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
        if (newRow !<= 7 || newRow !>= 0) return false;
        if (newCol !<= 7 || newCol !>= 0) return false;

	if (this->owner == 'W') { // chess piece is white
		if (curRow - 1 == newRow && (curCol - 1 == newCol || curCol == newCol || curCol + 1 == newCol)) {
			return true;
		} else {
			return false;
		}
	} else { // chess piece is black
		if (curRow + 1 == newRow && (curCol - 1 == newCol || curCol == newCol || curCol + 1 == newCol)) {
			return true;
		} else {
			return false;
		}
	}
}
