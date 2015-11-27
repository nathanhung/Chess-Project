#ifndef GAME_H
#define GAME_H
#include "tile.h"
class Controller;

class Game {
	char turn; // 'W' = player1's turn, 'B' = player2's turn
	Tile** theGrid;
	const int GRIDSIZE;
	Controller& controller; // change this to gameNotification?
	Player* players;

	Game(int n, Controller& controller, Player* p1, Player* p2. char turn);
	virtual ~Game() = 0;
};
#endif
