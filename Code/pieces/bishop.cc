#include "bishop.h"

Bishop::Bishop() {}

Bishop::~Bishop() {}


bool Bishop::checkMove(int curRow, int curCol, int newRow, int newCol) {
	// check if new position is out of board
        if (newRow !<= 7 || newRow !>= 0) return false;
        if (newCol !<= 7 || newCol !>= 0) return false;

	// check if its a valid diagonal move
	for (int i = 1; i <= 7; i++) {
                if (curRow - i == newRow && curCol + i == newCol) return true;
                if (curRow + i == newRow && curCol + i == newCol) return true;
                if (curRow + i == newRow && curCol - i == newCol) return true;
                if (curRow - i == newRow && curCol - i == newCol) return true;
        }
        return false;	
}
