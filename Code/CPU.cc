#include "CPU.h"
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include "pieces/chesspiece.h"
#include "tile.h"
#include "game.h"
#include <iostream>
#include "convert.h"
using namespace std;

CPU::CPU(int number, int level, Game* game): Player(number, game), level(level){}

CPU::~CPU(){}

bool CPU::isCPU(){
	return true;
}


string CPU::getMove(){
	string moves[100];
	assert (moves);
	int length = 0;
	// level 1 is random legal moves
	// level 2 is capturing > checking > random
	// level 3 is saving pieces > capturing > checks > random
	// level 4 is something more elaborate > saving pieces > capturing > checks > random
	assert(pieces && numPieces);
	string move = "a2a4";
	if(level == 4){ return move; }
	else if(level >= 3){ return move; }
	else if(level >= 2){ return move; }
	// level 1
	srand (time(NULL));

	int newRow;
	int newCol;
	
	while(!game->stalemate(playerNumber)){ //whats this loop for?
		newRow = rand() % 8;
		newCol = rand() % 8;
		for(int i = 0; i < numPieces; i++){
			assert(pieces[i] && pieces[i]->getPiece());
			//ChessPiece* piece = pieces[i]->getPiece();
			int curRow = pieces[i]->getRow();
			int curCol = pieces[i]->getColumn();

			// assert(curRow > -1 && curRow < 8);
			// assert(curCol > -1 && curCol < 8);
			// assert(newRow > -1 && newRow < 8);
			// assert(newCol > -1 && newCol < 8);

			//cout  << toColumn(curCol) << toRow(curRow) << toColumn(newCol) <<  toRow(newRow) << endl;
			move = toColumn(curCol) + toRow(curRow)+  toColumn(newCol) + toRow(newRow);

			if(checkValid(curRow,curCol, newRow, newCol)){
				assert(move != "a2a4");
				moves[length] = move;
				assert(moves[length] != "");
				length++;
			}
		}
	}
	
	assert(length);
	int random = rand() % length;
	assert(random);
	return moves[random];
}
