#include "knight.h"

Knight::~Knight() {}

Knight::Knight(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

bool Knight::checkMove(int curRow, int curCol, int newRow, int newCol) {
	if (newRow !<= 7 || newRow !>= 0) return false;
        if (newCol !<= 7 || newCol !>= 0) return false; // check if new position is out of board	
	
	if (curRow + 1 == newRow || curRow - 1 == newRow) {
		if (curCol + 2 == newCol || curCol - 2 == newCol) {
			return true;
		} else {
			return false;
		}
	}
	if (curCol + 1 == newCol || curCol - 1 == newCol) {
		if (curRow + 2 == newRow || curRow - 2 == newRow) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}
