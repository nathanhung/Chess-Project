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
	//gd = new GraphicDisplay():
	players = NULL;
}

Controller::~Controller(){
	delete game;
	delete td;
	//delete gd;
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
		else if(cmd == "resign"){
			if(game->turn == 'W'){
				WWins++;
			}
			else{
				BWins++;
			}
			delete game;
		}
		else if(cmd == "move"){
			// REMEMBER THE NUMBERS ARE INVERTED
			string spot1, spot2, pieceType;
			cmd >> spot1 >> spot2;

			int curRow = 8 - spot1.at(1) - '0';
			int newRow = 8 - spot2.at(1) - '0';
			char curCol = spot1.at(0);
			char newCol = spot2.at(0);

			// remember to check for pawn promotion
			// first check if its a pawn then see if spot2 is the edge of the board
			// through game->theGrid 
			Tile currentTile = game->theGrid(curRow, curCol - 'a');
			if(currentTile->chessPiece){ //if there is a chessPiece at the first coord
				// check to see if its a pawn
				if(currentTile->chessPiece->pieceType == 'p' && newRow == 7){
					// pawn promotion happening for BLACK
					cin >> pieceType; // piece player wants for promotion
					players[1]->promotePawn(); // what fields are required here?
					// TODO
					continue;
				}
				else if(currentTile->chessPiece->pieceType == 'P' && newRow == 0){
					// pawn promotion happening for WHITE
					cin >> pieceType; // piece player wants for promotion
					players[1]->promotePawn();
					continue;
				}
			}

			if(turn == 'W'){
				players[0]->checkValid(curRow, curCol, newRow, newCol);
			}
			else {
				players[1]->checkValid(curRow, curCol, newRow, newCol);
			}
		}
		else if()
		td->print();
	}
}
