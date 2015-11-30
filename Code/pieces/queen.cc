#include "queen.h"

Queen::Queen() {}

Queen::~Queen() {}

Queen::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
	if (newRow !<= 7 || newRow !>= 0) return false;
        if (newCol !<= 7 || newCol !>= 0) return false;

	// check possible vertical/horizontal moves
        for (int row = curRow; row <= 7; row++) {
                if (row == newRow && curCol == newCol) return true;
        }
        for (int row = curRow; row >= 0; row--) {
                if (row == newRow && curCol == newCol) return true;
        }
        for (int col = curCol; col <= 7; col++) {
                if (col == newCol && curRow == newRow) return true;
        }
        for (int col = curCol; col >= 0; col--) {
                if (col == newCol && curRow == newRow) return true;
        }

	// possible diagonal moves
	for (int i = 1; i <= 7; i++) {
		if (curRow - i == newRow && curCol + i == newCol) return true;
		if (curRow + i == newRow && curCol + i == newCol) return true;
		if (curRow + i == newRow && curCol - i == newCol) return true;
		if (curRow - i == newRow && curCol - i == newCol) return true;
	}
	return false;
}
