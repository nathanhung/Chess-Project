
#include "tile.h"
class Controller;

class Game {
	Tile** theGrid;
	const int GRIDSIZE;
	Controller& controller; // change this to gameNotification?

	Game(int n, Controller& controller);
	virtual ~Game() = 0;
};
