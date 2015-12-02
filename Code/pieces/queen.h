#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"
class Game;
class Queen: public ChessPiece {
public:
	Queen(char owner, char type, Game* game);
	~Queen();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};
#endif
