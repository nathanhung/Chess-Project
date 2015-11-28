#ifndef TILE_H
#define TILE_H
#include "pieces/chesspiece.h"

class Game;

class Tile {
	int row;
	char column;
	ChessPiece* piece;
	Game* game;

	Tile(Game* game);
	virtual ~Tile() = 0;

public:
	void notify(int row1, int col1, int row2, int col2);
	void setCoords(int row, int col);
	bool checkValid(int newRow, int newCol); // is the move valid? If no piece return true
};
#endif
