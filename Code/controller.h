#include <string>
using namespace std;

class View;
class Game;
class Player;

class Controller {
	string turn;
	int BWins, WWins;
	Game* game;
	View* view;
	Player* players;

public:
	void game(Player p1, Player p2); // what does this do?
	void gameNotify(int row1, char col1, int row2, char col2);
	void resign();
	void move(int row, char col);
	void setup();
	void viewNotify(int row, int col, char newChar);

	Controller();
	virtual ~Controller() = 0;
};
