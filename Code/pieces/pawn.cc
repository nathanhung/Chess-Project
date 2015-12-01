#include "pawn.h"

Pawn::Pawn(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

Pawn::~Pawn() {}

bool Pawn::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
        if (newRow !<= 7 || newRow !>= 0) return false;
        if (newCol !<= 7 || newCol !>= 0) return false;
	
	// check if move is reachable
	int validCheck = 0;
	int movedTwo = 0;
	if (this->owner == 'W') { // chess piece is white
		if (curRow - 1 == newRow && (curCol - 1 == newCol || curCol == newCol || curCol + 1 == newCol)) {
			validCheck = 1;
		}
		if (curRow == 6 && newRow == 4 && curCol == newCol) {
			validCheck = 1; 
			movedTwo = 1;
		}
	} else { // chess piece is black
		if (curRow + 1 == newRow && (curCol - 1 == newCol || curCol == newCol || curCol + 1 == newCol)) {
			validCheck = 1;
		}
		if (curRow == 1 && newRow == 3 && curCol == newCol) {
			validCheck = 1;
			movedTwo = 1;
		}
	}
	if (validCheck == 0) return false; // new position is unreachable
	if (movedTwo == 1) {
		if (this->owner == 'W') {
			if (game->getTile(curRow - 1, newCol)->getPiece()) return false;
		} else {
			if (game->getTile(curRow + 1, newCol)->getPiece()) return false;
	} 
	return true;
}
