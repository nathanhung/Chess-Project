#include "queen.h"
#include "../game.h"

Queen::Queen(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

Queen::~Queen() {}

Queen::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
	if (newRow !<= 7 || newRow !>= 0) return false;
        if (newCol !<= 7 || newCol !>= 0) return false;

	int reached = 0;
	int reachByHor = 0;
	int reachByDiag = 0;	

	// check possible vertical/horizontal moves
	if (curRow == newRow || curCol == newCol) {
		reached = 1;
		reachByHor = 1;
	}

	// check possible diagonal moves
        for (int i = 1; i <= 7; i++) {
                if (curRow - i == newRow && curCol + i == newCol) {
			reached = 1;
			reachByDiag = 1;
		}
                if (curRow + i == newRow && curCol + i == newCol) {
			reached = 1;
			reachByDiag = 1;
		}
                if (curRow + i == newRow && curCol - i == newCol) {
			reached = 1;
			reachByDiag = 1;
		}
                if (curRow - i == newRow && curCol - i == newCol) {
			reached = 1;
			reachByDiag = 1;
        }
        if (reached = 0) return false;
	
	// check if a piece is in the way from current to new position
	if (reachByHor = 1) {
		if (curRow == newRow) {
                	if (curCol < newCol) {
                        	for (int i = curCol; i < newCol; i++) {
                                	if (game->getTile(newRow, i)->getPiece()) return false;
                        	}
                	} else {
                        	for (int i = curCol; i > newCol; i--) {
                                	if (game->getTile(newRow, i)->getPiece()) return false;
                        	}
                	}
        	}
        	if (curCol == newCol) {
                	if (curRow < newRow) {
                        	for (int i = curRow; i < newRow; i++) {
                                	if (game->getTile(i, newCol)->getPiece()) return false;
                        	}
                	} else {
                        	for (int i = curRow; i > newRow; i--) {
                                	if (game->getTile(i, newCol)->getPiece()) return false;
                        	}
                	}
        	}		
	}
	if (reachByDiag = 1) {
		if (curRow > newRow && curCol > newCol) {
                	for (int i = curRow, int j = curCol; i > newRow && j > newCol; i--, j--) {
                        	if (game->getTile(i, j)->getPiece()) return false;
                	}
        	} else if (curRow < newRow && curCol > newCol) {
                	for (int i = curRow, int j = curCol; i < newRow, j > newCol; i++, j--) {
                        	if (game->getTile(i, j)->getPiece()) return false;
                	}
        	} else if (curRow > newRow && curCol < newCol) {
                	for (int i = curRow, int j = curCol; i > newRow, j < newCol; i--, j++) {
                        	if (game->getTile(i, j)->getPiece()) return false;
                	}
        	} else if (curRow > newRow && curCol > newCol) {
                	for (int i = curRow, int j = curCol; i > newRow, j > newCol; i--, j--) {
                        	if (game->getTile(i, j)->getPiece()) return false;
                	}
        	}		
	}
	return true;
}
