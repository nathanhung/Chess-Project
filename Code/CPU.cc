#include "CPU.h"
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include "pieces/chesspiece.h"
#include "tile.h"
using namespace std;

CPU::CPU(int number, int level): Player(number), level(level){}

CPU::~CPU(){}

string CPU::getMove(){
	// level 1 is random legal moves
	// level 2 is capturing > checking > random
	// level 3 is saving pieces > capturing > checks > random
	// level 4 is something more elaborate > saving pieces > capturing > checks > random
	assert(pieces && numPieces);
	string move = "a0";
	if(level == 4){ return move; }
	else if(level >= 3){ return move; }
	else if(level >= 2){ return move; }
	// level 1
	srand (time(NULL));

	int newRow = rand() % 8;
	int newCol = rand() % 8;
	
	while(true){
		for(int i = 0; i < numPieces; i++){
			assert(pieces[i] && pieces[i]->getPiece());
			ChessPiece* piece = pieces[i]->getPiece();
			int curRow = pieces[i]->getRow();
			int curCol = pieces[i]->getColumn();
			string move = "a0";
			if(piece->checkMove(curRow,curCol, newRow, newCol)){
				// TODO
				return move;
			}
		}
		// TODO
		return move;
	}
	
}
