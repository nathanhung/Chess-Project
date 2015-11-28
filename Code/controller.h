#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
using namespace std;

class View;
class Game;
class Player;
class TextDisplay;
class GraphicDisplay;

class Controller {
	string turn;
	int BWins, WWins;
	Game* game;
	TextDisplay* td;
	GraphicDisplay* gd;
public:
	void playGame(); // command interpreter for game
	void makeGame(string p1, string p2); // starts a new game when "game player player" is read in
	void gameNotify(int row1, char col1, int row2, char col2);
	void resign();
	void move(int row, char col);
	void setup();
	void viewNotify(int row, int col, char newChar);

	Controller();
	virtual ~Controller() = 0;
};
#endif
