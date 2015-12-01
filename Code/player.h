#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class ChessPiece;
class Tile;

class Player {
	Tile** theGrid;
	Tile* pieces[16];
	int numPieces;
	Tile* king1,* king2;
	
public:
	Player();
	virtual ~Player() = 0;
	bool checkValid (int curRow, char curCol, int newRow, char newCol);
	void setGrid(Tile** theGrid);
	Tile* getPiece(int index);
	void addPiece(Tile* piece);
	void removePiece(Tile* tile);
	void setKing1(Tile* king);
	void setKing2(Tile* king);
	void promotePawn(char pieceType);
};

#endif
