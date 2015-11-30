#include "king.h"

King::King() {} 

King::~king() {} // dtor

bool King::checkMove(int curRow, int curCol, int newRow, int newCol) {
	if (newRow !<= 7 || newRow !>= 0) return false;
	if (newCol !<= 7 || newCol !>= 0) return false; // check if new position is out of board
	
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
