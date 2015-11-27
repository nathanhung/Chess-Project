#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class ChessPiece;
class Tile;

class Player {
	Tile** theGrid;
	ChessPiece* pieces;
	int numPieces;
	
public:
	Player();
	virtual ~Player() = 0;
	virtual string getMove() = 0;
};

#endif
