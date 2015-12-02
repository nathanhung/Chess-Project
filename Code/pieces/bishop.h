#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"
class Game;
class Bishop: public ChessPiece {
public:
	Bishop(char owner, char type, Game* game);
	~Bishop();
	bool checkMove(int curRow, int curCol, int newRow, int newCol);
};
#endif
