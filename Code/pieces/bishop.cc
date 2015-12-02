#include "bishop.h"
#include "../game.h"

Bishop::Bishop(char owner, char type, Game *game): ChessPiece(owner, type, game) {}

Bishop::~Bishop() {}

bool Bishop::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
        if (newRow > 7 || newRow < 0) return false;
        if (newCol > 7 || newCol < 0) return false;
	if (curRow == newRow || curCol == newCol) return false;
	
	// check if its a valid diagonal move
	int reached = 0;
	for (int i = 1; i <= 7; i++) {
            if (curRow - i == newRow && curCol + i == newCol) reached = 1;
            if (curRow + i == newRow && curCol + i == newCol) reached = 1;
            if (curRow + i == newRow && curCol - i == newCol) reached = 1;
            if (curRow - i == newRow && curCol - i == newCol) reached = 1;
        }
        if (reached == 0) return false;
    int i = curRow;
    int j = curCol;
	// check if pieces are in the way
	if (curRow > newRow && curCol > newCol) {
		for (; i > newRow && j > newCol; i--, j--) {
			if (game->getTile(i, j)->getPiece()) return false;
		} 
	} else if (curRow < newRow && curCol > newCol) {
		for (; i < newRow && j > newCol; i++, j--) {
			if (game->getTile(i, j)->getPiece()) return false;
		}
	} else if (curRow > newRow && curCol < newCol) {
		for (; i > newRow && j < newCol; i--, j++) {
                        if (game->getTile(i, j)->getPiece()) return false;
                }
	} else if (curRow > newRow && curCol > newCol) {
		for (; i > newRow && j > newCol; i--, j--) {
                        if (game->getTile(i, j)->getPiece()) return false;
                }
	}
	return true;
}
