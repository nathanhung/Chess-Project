#ifndef TILE_H
#define TILE_H
#include "pieces/chesspiece.h"
class Game;

class Tile {
	int row, column;
	ChessPiece* piece;
	Game* game;
public:
	Tile();
	virtual ~Tile();
	void notify(int curRow, int curCol, int newRow, int newCol);
	void setCoords(int row, int col);
	bool checkValid(int newRow, int newCol); // is the move valid? If no piece return true
	void setPiece(ChessPiece* cp);
	ChessPiece* getPiece();
	void setGame(Game* g);
	int getRow();
	int getColumn();
};
#endif
