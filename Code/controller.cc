#include "controller.h"
#include <iostream>
#include "game.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include <string>
#include <cstdlib>
using namespace std;

Controller::Controller(){
	game = NULL;
	td = new TextDisplay();
	gd = new GraphicDisplay():
	players = NULL;
}

Controller::~Controller(){
	delete game;
	delete td;
	delete gd;
}
void Controller::makeGame(string p1, string p2){
	// player1
	// if human
	if (p1 == "human"){
		players[0] = new Human();
	} 
	// otherwise its a CPU
	else {
		int level = p1.back - '0';
		players[0] = new CPU(level);
	}

	// player2
	// if human
	if (p12== "human"){
		players[1] = new Human();
	} 
	// otherwise its a CPU
	else {
		int level = p2.back - '0';
		players[1] = new CPU(level);
	}
	game = new Game(8, *this, players[0], players[1], 'W');
	// TODO
	// setup views and print 
}

Controller::playGame(){
	string cmd;
	// int moves;
	while (cin >> cmd){
		// new game
		if (cmd == "game"){
			string p1, p2;
			cin >> p1 >> p2;
			makeGame();
		}
	}
}
