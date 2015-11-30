#include "player.h"
#include "tile.h"

Player::Player(): theGrid(NULL), numPieces(0), pieces(NULL), kin1(NULL), kin2(NULL){}

void Player::setGrid(Tile** theGrid){
	theGrid = theGrid;
}

void Player::addPiece(Tile piece){
	pieces[numPieces] = piece;
	numPieces++;
}

void Player::setKing1(Tile* king){
	king1 = king;
}

void Player::setKing2(Tile* king){
	king2 = king;
}
