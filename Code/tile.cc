#include "tile.h"
#include <cstdlib>
using namespace std;

Tile::Tile(): game(NULL), piece(NULL){}

Tile::~Tile(){
	delete ChessPiece;
	delete this;
}

void Tile::notify (int row1, int col1, int row2, int col2) {
	if (piece) {
		game->notifierNotify(row2, col2, piece->type);
	} 
	else 
	{
		char c = ((row2 + col2) % 2)? ' ' : '-';
		game->notifierNotify(row2, col2, c);
	} 
}

void Tile::setCoords(int row, int col) {
	row = row;
	column = col;
}

bool Tile::checkValid(int newRow, int newCol) {
	if (piece != NULL) {
		return piece->checkMove(row, col, newRow, newCol); // checks if move is valid
	} else {
		return false;
	}

void Tile::setPiece(ChessPiece* cp){
	piece = cp;
}

ChessPiece* Tile::getPiece(){
	return piece;
}

void Tile::setGame(Game* g){
	game = g;
}
