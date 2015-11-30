#include "CPU.h"
#include <ctime>
#include <cstdlib>

CPU::CPU(int level): level(level){}

CPU::~CPU(){}

string CPU::getMove(){
	// level 1 is random legal moves
	// level 2 is capturing > checking > random
	// level 3 is saving pieces > capturing > checks > random
	// level 4 is something more elaborate > saving pieces > capturing > checks > random
	assert(pieces && numPieces);

	if(level == 4){}
	else if(level >= 3){}
	else if(level >= 2){

	}
	// level 1
	srand (time(NULL));

	int newRow = rand() % 8;
	int newCol = rand() % 8;
	
	while(){
		for(int i = 0; i < numPieces; i++){
			assert(pieces[i] && pieces[i]->getPiece());
			ChessPiece* piece = pieces[i]->getPiece();
			int curRow = pieces[i]->getRow();
			int curCol = pieces[i]->getColumn();

			if(piece->checkMove(curRow,curCol, newRow, newCol)){
				// return move
			}
		}
		return move;
	}
	
}
