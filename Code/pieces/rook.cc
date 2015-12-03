#include "rook.h"
#include "../game.h"

Rook::Rook(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

Rook::~Rook() {}

bool Rook::checkMove (int curRow, int curCol, int newRow, int newCol) {
	if (newRow > 7 || newRow < 0) return false;
        if (newCol > 7 || newCol < 0) return false; // check if new position is out of board
	if (curRow == newRow && curCol == newCol) return false; 	

	// check if piece is reachable from current position
	if (curRow != newRow && curCol != newCol) return false;
	
	// check if a chess piece is in the way of old position to new position
	if (curRow == newRow) {
		if (curCol < newCol) {
			for (int i = curCol + 1; i < newCol; i++) {
				if (game->getTile(newRow, i)->getPiece()) return false;
			}	
		} else {
			for (int i = curCol - 1; i > newCol; i--) {
				if (game->getTile(newRow, i)->getPiece()) return false;
			}
		}
	}
	if (curCol == newCol) {
		if (curRow < newRow) {
			for (int i = curRow + 1; i < newRow; i++) {
				if (game->getTile(i, newCol)->getPiece()) return false;
			}
		} else {
			for (int i = curRow - 1; i > newRow; i--) {
				if (game->getTile(i, newCol)->getPiece()) return false;
			}
		}
	}
	return true;
}
