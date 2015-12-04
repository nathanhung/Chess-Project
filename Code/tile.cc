#include "tile.h"
#include <cstdlib>
#include "game.h"
#include "pieces/chesspiece.h"
#include <cassert>
using namespace std;

Tile::Tile(): game(NULL), piece(NULL){}

Tile::~Tile(){
	if(piece){
		delete piece;
	}
}

void Tile::notify (int row1, int col1, int row2, int col2) {
	if(piece) {
		game->notifierNotify(row2, col2, piece->getType());
	} 
	else {
		char c = ((row2 + col2) % 2)? ' ' : '-';
		game->notifierNotify(row2, col2, c);
	} 
}

void Tile::setCoords(int i, int j) {
	this->row = i;
	this->column = j;
}

bool Tile::checkValid(int newRow, int newCol) {
	if (piece != NULL) {
		return piece->checkMove(row, column, newRow, newCol); // checks if move is valid
	} else {
		return false;
	}
}

void Tile::setPiece(ChessPiece* cp){
	piece = cp;
}

ChessPiece* Tile::getPiece(){
	return piece;
}

void Tile::setGame(Game* g){
	game = g;
	assert(game);
}

int Tile::getRow(){
	return row;
}

int Tile::getColumn(){
	return column;
}
