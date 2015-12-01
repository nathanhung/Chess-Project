#include "controller.h"
#include <iostream>
#include "game.h"
#include "views/textdisplay.h"
#include "views/graphicdisplay.h"
#include "human.h"
#include "CPU.h"
#include <string>
#include <cstdlib>
using namespace std;

Controller::Controller(): game(NULL), setup(false), BWins(0), WWins(0){
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
	
	game = new Game(8, *this, p1, p2, 'W');

	// TODO
	// setup views and print 
}

void Controller::playGame(){
	string cmd;
	// int moves;
	while (cin >> cmd){ // remember to update view and print after each command
		// new game
		if (cmd == "game"){
			string p1, p2;
			cin >> p1 >> p2;
			makeGame(p1, p2);
		}
		else if(cmd == "resign"){
			if(game->getTurn() == 'W'){
				WWins++;
			}
			else{
				BWins++;
			}
			delete game;
		}
		else if(cmd == "move"){
			// REMEMBER THE NUMBERS ARE INVERTED
			string spot1, spot2;
			char pieceType;
			cin >> spot1 >> spot2;

			int curRow = toIndex(spot1.at(1) - '0');
			int newRow = toIndex(spot2.at(1) - '0');
			int curCol = toIndex(spot1.at(0));
			int newCol = toIndex(spot2.at(0));

			// remember to check for pawn promotion
			// first check if its a pawn then see if spot2 is the edge of the board
			// through game->getTile 
			Tile* currentTile = game->getTile(curRow, curCol);
			Tile* newTile = game->getTile(newRow, newCol);
			if(currentTile->getPiece()){ //if there is a chessPiece at the first coord
				// check to see if its a pawn
				if(currentTile->getPiece()->getType() == 'p' && newRow == 7){
					// pawn promotion happening for BLACK
					cin >> pieceType; // piece player wants for promotion
					game->promotePawn(curRow, curCol, pieceType); // what fields are required here?
					// TODO
					continue;// same as below
				}
				else if(currentTile->getPiece()->getType() == 'P' && newRow == 0){
					// pawn promotion happening for WHITE
					cin >> pieceType; // piece player wants for promotion
					game->promotePawn(curRow, curCol, pieceType);
					continue; // cant  do this, must redisplay board
					// must notify view
				}
			}
			// otherwise just move piece if possible
			if(turn == 'W'){
				if(!game->getPlayer(0)->checkValid(curRow, curCol, newRow, newCol)){
					cout << "Invalid Move." << endl; 
					continue;
				}

				// valid move, check for capture
				if(newTile->getPiece()){
					char type = newTile->getPiece()->getType();
					if(type >= 'a' && type <= 'z'){ // piece is black, we are white
						// delete it and replace all pointers to NULL
						game->getPlayer(1)->removePiece(newTile);
						delete newTile->getPiece();
					}
				}
			}
			else {
				if(!game->getPlayer(1)->checkValid(curRow, curCol, newRow, newCol)){
					cout << "Invalid Move." << endl; 
					continue;
				}
				// valid move, check for capture
				if(newTile->getPiece()){
					char type = newTile->getPiece()->getType();
					if(type >= 'A' && type <= 'Z'){ // piece is white, we are black
						// delete it and replace all pointers to NULL
						game->getPlayer(0)->removePiece(newTile);
						delete newTile->getPiece();
					}
				}
			}
			// must change coords and notify view here
			game->getTile(curRow, curCol)->setCoords(newRow, newCol);
			game->getTile(newRow, newCol)->setCoords(curRow, curCol);
			game->swapTiles(currentTile, newTile);
			if(currentTile->getPiece()){
				
			}
			if(newTile->getPiece()){

			}
			viewNotify(newRow, newCol, newTile->getPiece()->getType());
			viewNotify(curRow, curCol, currentTile->getPiece()->getType());
		}
		// setup
		else if(cmd == "setup"){
			delete game;
			makeGame("human", "human");
			cin >> cmd;

			while(cmd != "done"){
				char op = cmd.at(0);
				// start accepting input
				// + - =
				if(op == '+'){
					char piece;
					string location;
					cin >> piece >> location;

					ChessPiece* cp = new ChessPiece(piece);
					int curRow = toIndex(location.at(1));
					int curCol = toIndex(location.at(0));

					// set piece at location
					Tile* currentTile = game->getTile[curRow][curCol];
					currentTile->getPiece() = cp;

					if(piece >= 'A' && piece <= 'Z'){
						game->getPlayer(0)->pieces[numPieces] = cp;
					}
					else{
						game->getPlayer(1)->addPiece(cp);
					}
					// notify view of the change
					viewNotify(curRow, curCol, piece);
				}
				else if(op == '-'){
					string location;

					cin >> location;
					int curRow = toIndex(location.at(1));
					int curCol = toIndex(location.at(0));

					Tile* currentTile = game->getTile[curRow][curCol];
					if(currentTile->getPiece()){
						delete currentTile->getPiece();
						currentTile = NULL;
					}
					if((curRow +curCol) % 2) { // black tile
						viewNotify(curRow, curCol, '-');
					}
					else{
						viewNotify(curRow, curCol, ' ');	
					}
				} 
				else if(op == '='){
					string colour;
					cin >> colour;
					if(colour == "white"){
						game->getTurn() = 'W';
					}
					else{
						game->getTurn() = 'B';
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
