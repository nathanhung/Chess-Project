#include "pawn.h"
#include "../game.h"

Pawn::Pawn(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

Pawn::~Pawn() {}

bool Pawn::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
        if (newRow > 7 || newRow < 0) return false;
        if (newCol > 7 || newCol < 0) return false;
	

	// check diagonal moves
	char pieceType;
	if (this->owner == 'W') {
		if (curRow - 1 == newRow && (curCol - 1 == newCol || curCol + 1 == newCol)) {
			if (game->getTile(newRow, newCol)->getPiece()) {
				pieceType = game->getTile(newRow, newCol)->getPiece()->getType();
				if (pieceType >= 'A' && pieceType <= 'Z') return false;
				return true;
			} else {
				if (game->getEnPassant() == false) return false;
				if (!(game->getTile(curRow, newCol)->getPiece())) return false;
				pieceType = game->getTile(curRow, newCol)->getPiece()->getType();
				if (pieceType >= 'A' && pieceType <= 'Z') return false;
				return true;
			}
		}
	} else {
		if (curRow + 1 == newRow && (curCol - 1 == newCol || curCol + 1 == newCol)) {
                        if (game->getTile(newRow, newCol)->getPiece()) {
                                pieceType = game->getTile(newRow, newCol)->getPiece()->getType();
                                if (pieceType >= 'a' && pieceType <= 'z') return false;
				return true;
                        } else {
                                if (game->getEnPassant() == false) return false;
                                if (!(game->getTile(curRow, newCol)->getPiece())) return false;
                                pieceType = game->getTile(curRow, newCol)->getPiece()->getType();
                                if (pieceType >= 'a' && pieceType <= 'z') return false;
				return true;
                        }
                }
	}		
	// check one step vertical moves
	if (owner == 'W') {
		if (curRow - 1 == newRow && curCol == newCol) {
			if (game->getTile(newRow, newCol)->getPiece()) return false;
			return true;
		}
	} else {
		if (curRow + 1 == newRow && curCol == newCol) {
			if (game->getTile(newRow, newCol)->getPiece()) return false;
			return true;
		}
	}
	
	// check possible two step vertical moves	
	if (owner == 'W') {
		if (curRow == 6 && newRow == 4 && curCol == newCol) {
			if (game->getTile(curRow - 1, newCol)->getPiece()) return false;
                	if (game->getTile(curRow - 2, newCol)->getPiece()) return false;
			game->setEnPassant(true);
			return true;	
		}
	} else {
		if (curRow == 1 && newRow == 3 && curCol == newCol) {
			if (game->getTile(curRow + 1, newCol)->getPiece()) return false;
                	if (game->getTile(curRow + 2, newCol)->getPiece()) return false;
			game->setEnPassant(true);
			return true;
		}
	}
	return false;
}
