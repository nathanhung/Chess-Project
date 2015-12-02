#include "player.h"
#include "tile.h"

Player::Player(): theGrid(NULL), numPieces(0), pieces(NULL), king1(NULL), king2(NULL){}

void Player::setGrid(Tile** theGrid){
	theGrid = theGrid;
}

void Player::addPiece(Tile* piece){
	pieces[numPieces] = piece;
	numPieces++;
}

void Player::setKing1(Tile* king){
	king1 = king;
}

void Player::setKing2(Tile* king){
	king2 = king;
}

// gets a piece from pieces array
Tile* Player::getPiece(int index){
	return pieces[index];
}

void Player::removePiece(Tile* tile){
	// find tile in our pieces array, and shift to left, deleting happens in cont
	int i;
	for(i = 0; i < numPieces; i++){
		if(tile == pieces[i]){
			break;
		}
	}
	for(; i < numPieces - 1; i++){
		pieces[i] = pieces[i+1];
	}
	numPieces--;
}

int Player::getNumPieces(){
	return numPieces;
}
