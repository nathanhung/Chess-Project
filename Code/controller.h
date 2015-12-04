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
	char turn;
	int BWins, WWins;
	bool setup;
	Game* game;
	TextDisplay* td;
	GraphicDisplay* gd;
public:
	void playGame(); // command interpreter for game
	void makeGame(string p1, string p2); // starts a new game when "game player player" is read in
	void gameNotify(int row1, char col1, int row2, char col2);
	void resign();
	void viewNotify(int row, int col, char newChar);
	void updateViews();
	Controller(std::string);
	virtual ~Controller();
};
#endif
