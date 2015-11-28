#include "controller.h"
#include <iostream>
#include "game.h"
#include "views/textdisplay.h"
#include "views/graphicdisplay.h"
#include <string>
#include <cstdlib>
using namespace std;

Controller::Controller(): game(NULL){
	td = new TextDisplay(8);
	//gd = new GraphicDisplay():
}

Controller::~Controller(){
	delete game;
	delete td;
	//delete gd;
}

int toIndex(char c){
	return  c - 'a';
}
// assumes we have an integer (do - '0')
int toIndex(int n){
	return  8 - n;
}

void Controller::makeGame(string p1, string p2){
	// player1
	// if human
	if (p1 == "human"){
		game->setPlayer(new Human(), 0);
	} 
	// otherwise its a CPU
	else {
		int level = p1.back() - '0';
		game->setPlayer(new CPU(level), 0);
	}

	// player2
	// if human
	if (p12== "human"){
		game->setPlayer(new Human(), 1);
	} 
	// otherwise its a CPU
	else {
		int level = p2.back() - '0';
		game->setPlayer(new CPU(level), 1);
	}

	game = new Game(8, *this, players[0], players[1], 'W');

	// TODO
	// setup views and print 
}

Controller::playGame(){
	string cmd;
	// int moves;
	while (cin >> cmd){ // remember to update view and print after each command
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

			int curRow = toIndex(spot1.at(1) - '0');
			int newRow = toIndex(spot2.at(1) - '0');
			int curCol = toIndex(spot1.at(0));
			int newCol = toIndex(spot2.at(0));

			// remember to check for pawn promotion
			// first check if its a pawn then see if spot2 is the edge of the board
			// through game->theGrid 
			Tile currentTile = game->theGrid(curRow, curCol);
			if(currentTile->chessPiece){ //if there is a chessPiece at the first coord
				// check to see if its a pawn
				if(currentTile->chessPiece->pieceType == 'p' && newRow == 7){
					// pawn promotion happening for BLACK
					cin >> pieceType; // piece player wants for promotion
					players[1]->promotePawn(); // what fields are required here?
					// TODO
					continue;// same as below
				}
				else if(currentTile->chessPiece->pieceType == 'P' && newRow == 0){
					// pawn promotion happening for WHITE
					cin >> pieceType; // piece player wants for promotion
					players[1]->promotePawn();
					continue; // cant  do this, must redisplay board
					// must notify view
				}
			}
			// otherwise just move piece if possible
			if(turn == 'W'){
				players[0]->checkValid(curRow, curCol, newRow, newCol);
			}
			else {
				players[1]->checkValid(curRow, curCol, newRow, newCol);
			}
		}
		// setup
		else if(cmd == "setup"){
			delete game;
			makeGame();
			cin >> cmd;

			while(cmd != "done"){
				// start accepting input
				// + - =
				if(cmd == '+'){
					char piece;
					string location;
					cin >> piece >> location;

					ChessPiece* cp = new ChessPiece(piece);
					int curRow = toIndex(location.at(1));
					int curCol = toIndex(location.at(0));

					// set piece at location
					Tile* currentTile = game->theGrid[curRow][curCol];
					currentTile->chessPiece = cp;

					if(piece.isupper()){
						players[0]->pieces[numPieces] = cp;
					}
					else{
						players[1]->pieces[numPieces] = cp;
					}
					// notify view of the change
					viewNotify(curRow, curCol, piece);
				}
				else if(cmd == '-'){
					string location;

					cin >> location;
					int curRow = toIndex(location.at(1));
					int curCol = toIndex(location.at(0));

					Tile* currentTile = game->theGrid[curRow][curCol];
					if(currentTile->chessPiece){
						delete currentTile->chessPiece;
						currentTile = NULL;
					}
					if((curRow +curCol) % 2) { // black tile
						viewNotify(curRow, curCol, '-');
					}
					else{
						viewNotify(curRow, curCol, ' ');	
					}
				} 
				else if(cmd == '='){
					string colour;
					cin >> colour;
					if(colour == "white"){
						game->turn = 'W';
					}
					else{
						game->turn = 'B';
					}
				}
				else{
					cout << "Invalid move!" << endl;
				}
			}
		}
		td->print();
	}
}
