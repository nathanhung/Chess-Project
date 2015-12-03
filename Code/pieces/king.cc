#include "king.h"
#include "../game.h"

King::King(char owner, char type, Game* game): ChessPiece(owner, type, game) {} 

King::~King() {} // dtor

bool King::checkMove(int curRow, int curCol, int newRow, int newCol) {
	if (newRow > 7 || newRow < 0) return false;
	if (newCol > 7 || newCol < 0) return false; // check if new position is out of board 

	// check for castle move
	char pieceType;
	if (this->owner = 'W') { // ownter is white
		if (curRow == 7 && newRow == 7 && curCol == 4 && newCol == 6) { // bottom right
			if (game->getTile(7,5)->getPiece()) return false;
			if (game->getTile(7,6)->getPiece()) return false;
			if (!(game->getTile(7,7)->getPiece())) return false;
			pieceType = game->getTile(7,7)->getPiece()->getType();
			if (pieceType != 'R') return false;
			return true;
		}
		if (curRow == 7 && newRow == 7 && curCol == 4 && newCol == 1) { // bottom left
			if (game->getTile(7,3)->getPiece()) return false;
			if (game->getTile(7,2)->getPiece()) return false;
			if (game->getTile(7,1)->getPiece()) return false;
			if (!(game->getTile(7,7)->getPiece())) return false;
			pieceType = game->getTile(7,0)->getPiece()->getType();
			if (pieceType != 'R') return false;
			return true;
		}	
	} else { // owner is black
		if (curRow == 0 && newRow == 0 && curCol == 4 && newCol == 6) { // top right
			if (game->getTile(0,5)->getPiece()) return false;
			if (game->getTile(0,6)->getPiece()) return false;
			if (!(game->getTile(0,0)->getPiece())) return false;
			pieceType = game->getTile(0,0)->getPiece()->getType();
			if (pieceType != 'r') return false;
			return true;
		}
		if (curRow == 0 && newRow == 0 && curCol == 4 && newCol == 1) { // top left
			if (game->getTile(0,3)->getPiece()) return false;
			if (game->getTile(0,2)->getPiece()) return false;
			if (game->getTile(0,1)->getPiece()) return false;
			if (!(game->getTile(0,0)->getPiece())) return false;
			pieceType = game->getTile(0,0)->getPiece()->getType();
			if (pieceType != 'r') return false;
			return true;
		}
	}
	// check if move is reachable from current position
	if (curRow == newRow && curCol + 1 == newCol) { // valid move to the right
		return true;
	} else if (curRow + 1 == newRow && curCol + 1 == newCol) { 
		return true;
	} else if (curRow + 1 == newRow && curCol == newCol) {
		return true;
	} else if (curRow + 1 == newRow && curCol - 1 == newCol) {
		return true;
	} else if (curRow == newRow && curCol - 1 == newCol) {
		return true;
	} else if (curRow - 1 == newRow && curCol - 1 == newCol) {
		return true;
	} else if (curRow - 1 == newRow && curCol == newCol) {
		return true;
	} else if (curRow - 1 == newRow && curCol + 1 == newCol) {
		return true;
	} else {
		return false; // newRow and newCol are unreachable by king
	}
	
}
