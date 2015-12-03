#include "pawn.h"
#include "../game.h"

Pawn::Pawn(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

Pawn::~Pawn() {}

bool Pawn::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
        if (newRow > 7 || newRow < 0) return false;
        if (newCol > 7 || newCol < 0) return false;
	
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
	
	// check if the diagonal move was valid	(en Passant check here)
	char pieceType;
	if (this->owner == 'W') {
		if ((curRow - 1 == newRow && curCol - 1 == newCol) || (curRow - 1 == newRow && curCol + 1 == newCol)) {
			if (!(game->getTile(newRow, newCol)->getPiece())) { // if new spot is empty
				if (game->getEnPassant() == false) return false;
				if (!(game->getTile(curRow, newCol)->getPiece())) return false;
				pieceType = game->getTile(curRow, newCol)->getPiece()->getType();
				if (pieceType >= 'A' && pieceType <= 'Z') return false; // cannot enPassant own piece
			}
		}
	} else {
		if ((curRow + 1 == newRow && curCol - 1 == newCol) || (curRow + 1 == newRow && curCol + 1 == newCol)) {
                        if (!(game->getTile(newRow, newCol)->getPiece())) { // if new spot is empty
                                if (game->getEnPassant() == false) return false;
                                if (!(game->getTile(curRow, newCol)->getPiece())) return false;
				pieceType = game->getTile(curRow, newCol)->getPiece()->getType();
				if (pieceType >= 'a' && pieceType <= 'z') return false;				
                        }
                }
	}	
	// if it was 2 unit move, check both squares passed are empty
	if (movedTwo == 1) {
		if (this->owner == 'W') {
			if (game->getTile(curRow - 1, newCol)->getPiece()) return false;
			if (game->getTile(curRow - 2, newCol)->getPiece()) return false;
		} else {
			if (game->getTile(curRow + 1, newCol)->getPiece()) return false;
			if (game->getTile(curRow + 2, newCol)->getPiece()) return false;
		}
	} 
	return true;
}
