#ifndef GAME_H
#define GAME_H
#include <string>
#include "tile.h"
#include "pieces/chesspiece.h"
#include "controller.h"

class Player;
class Game {
	char turn; // 'W' = player1's turn, 'B' = player2's turn
	Tile** theGrid;
	const int GRIDSIZE;
	Controller& controller; // change this to gameNotification?
	Player* players[2];
public:
	Game(int n, Controller& controller, std::string p1, std::string p2, char turn);
	virtual ~Game();
	void setPlayer(Player* p, int index);
	void tileNotify(int curRow, char curCol, int newRow, char newCol);
	void notifierNotify(int row, int col, char piece);
	char getTurn();
	void setTurn(char turn);
	Tile* getTile(int row, int col);
	void setTile(int row, int col, Tile* tile);
	Player* getPlayer(int n);
	void promotePawn(int row, int col, char pieceType);
	void swapTiles(Tile* currentTile, Tile* newTile);
	bool checkBoard();
};
#endif
