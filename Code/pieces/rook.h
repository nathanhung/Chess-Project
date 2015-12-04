#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"
class Game;
class Rook: public ChessPiece {
	bool castling;
public:
	Rook(char owner, char type, Game* game); 
	~Rook();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
	bool getCastling();
};
#endif
