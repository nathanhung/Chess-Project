#include "controller.h"
#include <iostream>
#include "game.h"
#include "views/textdisplay.h"
#include "views/graphicdisplay.h"
#include "human.h"
#include "CPU.h"
#include <string>
#include <cstdlib>
#include "pieces/rook.h"
#include "pieces/king.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/pawn.h"
#include "pieces/knight.h"
#include <cassert>
using namespace std;

Controller::Controller(): game(NULL), setup(false), BWins(0), WWins(0){
	td = new TextDisplay(8);
	assert(td);
	//gd = new GraphicDisplay():
}

Controller::~Controller(){
	delete game;
	delete td;
	//delete gd;
}

int Controller::toIndex(char c){
	assert(c >= 'a');
	return  c - 'a';
}
// assumes we have an integer (do - '0')
int Controller::toIndex(int n){
	assert(n >= 1);
	return  8 - n;
}

void Controller::makeGame(string p1, string p2){
	
	game = new Game(8, *this, p1, p2, 'W');

	// TODO
	// setup views and print 
}

void Controller::viewNotify(int row, int col, char c){
	td->notify(row, col, c);
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

			assert(curRow >= 0 && curRow <= 7);
			assert(curCol >= 0 && curCol <= 7);
			assert(newRow >= 0 && newRow <= 7);
			assert(newCol >= 0 && newCol <= 7);

			// remember to check for pawn promotion
			// first check if its a pawn then see if spot2 is the edge of the board
			// through game->getTile 
			Tile* currentTile = game->getTile(curRow, curCol);
			Tile* newTile = game->getTile(newRow, newCol);

			assert(currentTile);
			assert(newTile);

			// pawn promotion checks
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
			assert(game->getTurn());
			// otherwise just move piece if possible
			if(game->getTurn() == 'W'){
				assert(game->getPlayer(0) && game->getPlayer(1));
				if(!game->getPlayer(0)->checkValid(curRow, curCol, newRow, newCol)){
					cout << "Invalid Move. 1" << endl;
				}
				// valid move, check for capture, if not capturing, just moving piece to empty tile
				if(newTile->getPiece()){
					assert(newTile->getPiece()->getType());

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
					cout << "Invalid Move. 2 " << endl; 
				}
				// valid move, check for capture, if not capturing, just moving piece to empty tile
				if(newTile->getPiece()){
					char type = newTile->getPiece()->getType();
					if(type >= 'A' && type <= 'Z'){ // piece is white, we are black
						// delete it and replace all pointers to NULL
						game->getPlayer(0)->removePiece(newTile);
						delete newTile->getPiece();
					}
				}
			}
			cout << "Line 150 " << endl;
			// must change coords and notify view here
			currentTile->setCoords(newRow, newCol);
			newTile->setCoords(curRow, curCol);
			
			if(currentTile->getPiece()){ // put piece in CURRENT spot at NEW SPOT
				viewNotify(newRow, newCol, currentTile->getPiece()->getType());
			}
			else{
				char c = ((newRow + newCol) % 2)? '-': ' ';
				viewNotify(newRow, newCol, c);
			}
			if(newTile->getPiece()){
				viewNotify(curRow, curCol, newTile->getPiece()->getType());
			}
			else{
				char c = ((curRow + curCol) % 2)? '-': ' ';
				viewNotify(curRow, curCol, c);
			}
			game->setTurn((game->getTurn() == 'W')? 'B':'W');
			game->swapTiles(currentTile, newTile);
		}
		// setup
		else if(cmd == "setup"){
			delete game;
			makeGame("human", "human");
			cin >> cmd;

			while(cmd != "done" && !game->checkBoard()){
				char op = cmd.at(0);
				// start accepting input
				// + - =
				if(op == '+'){
					char piece;
					string location;
					cin >> piece >> location;

					// get Tile at location
					int curRow = toIndex(location.at(1));
					int curCol = toIndex(location.at(0));
					Tile* currentTile = game->getTile(curRow, curCol);

					char owner = (piece >= 'a' && piece <= 'z')? 'B': 'W';
					ChessPiece* cp;
					// Pawn
					if(piece == 'p' || piece + 32 == 'p'){
						cp = new Pawn(owner, piece, game);
					}
					// Bishop
					else if(piece == 'b' || piece + 32 == 'b'){
						cp = new Bishop(owner, piece, game);
					}
					// Rook
					else if(piece == 'r' || piece + 32 == 'r'){
						cp = new Rook(owner, piece, game);
					}
					// Queen
					else if(piece == 'q' || piece + 32 == 'q'){
						cp = new Queen(owner, piece, game);
					}
					// King
					else if(piece == 'k' || piece + 32 == 'k'){
						cp = new King(owner, piece, game);
						if(owner == 'W'){
							game->getPlayer(0)->setKing1(currentTile);
							game->getPlayer(1)->setKing1(currentTile);
						}
						else{
							game->getPlayer(0)->setKing2(currentTile);
							game->getPlayer(1)->setKing2(currentTile);
						}
					}
					// Knight
					else if(piece == 'n' || piece + 32 == 'n'){
						cp = new Knight(owner, piece, game);
					}
					// else ERROR
					else{
						cout << "INVALID PIECE TYPE IN SETUP MODE!" << endl;
					}
					

					// set piece at location
					currentTile->setPiece(cp);

					if(piece >= 'A' && piece <= 'Z'){
						game->getPlayer(0)->addPiece(currentTile);
					}
					else{
						game->getPlayer(1)->addPiece(currentTile);
					}
					// notify view of the change
					viewNotify(curRow, curCol, piece);
				}
				else if(op == '-'){
					string location;

					cin >> location;
					int curRow = toIndex(location.at(1));
					int curCol = toIndex(location.at(0));

					Tile* currentTile = game->getTile(curRow, curCol);
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
						game->setTurn('W');
					}
					else{
						game->setTurn('B');
					}
				}
				else{
					cout << "Invalid move!" << endl;
				}
				td->print();
			}
		}
		td->print();
	}
}
