#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class ChessPiece;
class Tile;

class Player {
	Tile** theGrid;
	Tile* pieces;
	int numPieces;
	
public:
	Player();
	virtual ~Player() = 0;
	virtual string getMove() = 0;
	bool checkValid (int curRow, char curCol, int newRow, char newCol);
	void setGrid(Tile** theGrid);
	void addPiece(Tile piece);
};

#endif
