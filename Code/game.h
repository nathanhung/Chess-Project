#ifndef GAME_H
#define GAME_H
#include <string>
#include "tile.h"
#include "pieces/chesspiece.h"

class Controller;
class Player;
class Game {
	char turn; // 'W' = player1's turn, 'B' = player2's turn
	Tile** theGrid;
	const int GRIDSIZE;
	Controller& controller; // change this to gameNotification
	Player* players[2];
	bool enPassant;
public:
	Game(int n, Controller& controller, std::string p1, std::string p2, char turn);
	Game(int n, Controller& controller, std::string filename);
	virtual ~Game();
	void setPlayer(Player* p, int index);
	void tileNotify(int curRow, char curCol, int newRow, char newCol);
	void notifierNotify(int row, int col, char piece);
	char getTurn();
	void setTurn(char turn);
	Tile* getTile(int row, int col);
	void setTile(int row, int col, Tile& tile);
	Player* getPlayer(int n);
	void promotePawn(int curRow, int curCol, int newRow, int newCol, char pieceType, char owner);
	void swapTiles(Tile* currentTile, Tile* newTile);
	bool checkBoard();
	bool getEnPassant();
	void setEnPassant(bool value);
	void setPiece(int row, int col, ChessPiece* piece);
	bool check(int index);
	bool checkmate(int index);
	bool stalemate(int index);
	void nextTurn();
	bool stillInCheck(int curRow, int curCol, int newRow, int newCol);
	// for testing
	Tile** getGrid();
};
#endif
