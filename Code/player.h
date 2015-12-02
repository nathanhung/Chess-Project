#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class ChessPiece;
class Tile;
class Game;
class Player {
	int playerNumber;
protected:
	Game* game;
	Tile* pieces[16];
	int numPieces;
	Tile* king1,* king2;
	
public:
	Player(int number);
	virtual ~Player() = 0;
	bool checkValid (int curRow, int curCol, int newRow, int newCol);
	void setGame(Game* game);
	Tile* getPiece(int index);
	void addPiece(Tile* piece);
	void removePiece(Tile* tile);
	void setKing1(Tile* king);
	void setKing2(Tile* king);
	void promotePawn(char pieceType);
	int getNumPieces();
};

#endif
