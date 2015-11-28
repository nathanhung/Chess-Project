#include "player.h"
#include "tile.h"

Player::Player(): theGrid(NULL), numPieces(0), pieces(NULL){}

void Player::setGrid(Tile** theGrid){
	theGrid = theGrid;
}

void Player::addPiece(Tile piece){
	pieces[numPieces] = piece;
	numPieces++;
}
