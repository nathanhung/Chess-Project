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
#include "convert.h"
#include <cassert>
using namespace std;

Controller::Controller(std::string display = "text"): game(NULL), setup(false), BWins(0), WWins(0), td(NULL), gd(NULL){
	td = new TextDisplay(8);
	assert(td);

	if(display == "graphics"){
		gd = new GraphicDisplay(8);
	}
}

Controller::~Controller(){
	delete game;
	//delete td;
	delete gd;
}
void Controller::updateViews(){
	if(gd){
		gd->update(game->getGrid());
		gd->print();
	}

	if(td){
		td->update(game->getGrid());
		td->print();
	}
}
void Controller::makeGame(string p1, string p2){
	
	game = new Game(8, *this, p1, p2, 'W');

	// TODO
	// setup views and print 
}

void Controller::viewNotify(int row, int col, char c){
	td->notify(row, col, c);
	if(gd){
		gd->notify(row, col, c);
	}
}

void Controller::resign(){
if(game->getTurn() == 'W'){
		WWins++;
	}
	else{
		BWins++;
	}
	
	delete game;
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
			resign();
		}
		else if(cmd == "move"){
			// REMEMBER THE NUMBERS ARE INVERTED
			int curRow;
			int newRow;
			int curCol;
			int newCol;
			char pieceType;

			Player* currentPlayer = (game->getTurn() == 'W')? game->getPlayer(0) : game->getPlayer(1);
			if(!currentPlayer->isCPU()){
				string spot1, spot2;
				cin >> spot1 >> spot2;

				curRow = rowToIndex(spot1.at(1) - '0');
				newRow = rowToIndex(spot2.at(1) - '0');
				curCol = colToIndex(spot1.at(0));
				newCol = colToIndex(spot2.at(0));

				assert(curRow >= 0 && curRow <= 7);
				assert(curCol >= 0 && curCol <= 7);
				assert(newRow >= 0 && newRow <= 7);
				assert(newCol >= 0 && newCol <= 7);
			}
			else{ // if cpu we get move from cpu
				// comes in form of "a2 a4"
				string move = currentPlayer->getMove();

				curRow = rowToIndex(move.at(0) - '0');
				newRow = rowToIndex(move.at(1) - '0');
				curCol = colToIndex(move.at(2));
				newCol = colToIndex(move.at(3));

				assert(curRow >= 0 && curRow <= 7);
				assert(curCol >= 0 && curCol <= 7);
				assert(newRow >= 0 && newRow <= 7);
				assert(newCol >= 0 && newCol <= 7);
			}
			
			// remember to check for pawn promotion
			// first check if its a pawn then see if spot2 is the edge of the board
			// through game->getTile 
			Tile* currentTile = game->getTile(curRow, curCol);
			Tile* newTile = game->getTile(newRow, newCol);

			assert(currentTile);
			assert(newTile);
			// ***********************CHECK BEGIN ***************************
			// check if player is IN check  right now
			// if he is, he must make a move that takes him out of check
			// ***********************CHECK FOR WHITE************************
			if(game->getTurn() == 'W' && game->check(0)){ // white in check, turn check not necessary here but precautionary
				// check to see if the move they're trying to make will take them out of check
				if(game->getPlayer(0)->checkValid(curRow, curCol, newRow, newCol)){ // move is valid
					// cases
					// king / piece moves to an empty square
					// move it there, check for check then undo if still check
					if(!newTile->getPiece()){
						game->setPiece(newRow, newCol, currentTile->getPiece());
						game->setPiece(curRow, curCol, NULL);
						// check if it was a valid move:
						if(game->check(0)){ // swaps them back 
							game->setPiece(curRow, curCol, newTile->getPiece());
							game->setPiece(newRow, newCol, NULL);
							cout << "Invalid move, you are still in check! (White)" << endl;
						}
					}
					// king /piece kills enemy piece
					// replace piece ptr to NULL while storing it in oppPiece, move our piece there
					// check for check
					// undo if still check: includes moving piece back and bringing it back
					// remember to kill piece if move is valid
					else{
						ChessPiece* oppPiece = newTile->getPiece(); 
						game->setPiece(newRow, newCol, currentTile->getPiece());
						game->setPiece(curRow, curCol, NULL);
						if(game->check(0)){ // if still in check, move pieces pack
							game->setPiece(curRow, curCol, newTile->getPiece());
							game->setPiece(newRow, newCol, oppPiece);
							cout << "Invalid move, you are still in check! (White)" << endl;
						}
						else{ // it is a valid move, we must delete the piece and remove from player's pieces
							// if valid we must FIRST swap back, DELETE THEN MOVE cur piece to new tile
							game->setPiece(curRow, curCol, newTile->getPiece());
							game->setPiece(newRow, newCol, oppPiece);

							game->getPlayer(1)->removePiece(newTile);
							delete newTile->getPiece();
							// now assume piece is moving to empty square
							game->setPiece(newRow, newCol, currentTile->getPiece());
							game->setPiece(curRow, curCol, NULL);
						}
					}

					game->getPlayer(0)->setPiece(currentTile, newTile);
					updateViews();
					game->nextTurn();
					continue;// same as below 
				} 
			}
			// ************************CHECK FOR BLACK***************************
			if(game->getTurn() == 'B' && game->check(1)){ // white in check, turn check not necessary here but precautionary
				// check to see if the move they're trying to make will take them out of check
				if(game->getPlayer(1)->checkValid(curRow, curCol, newRow, newCol)){ // move is valid
					// cases
					// king / piece moves to an empty square
					// move it there, check for check then undo if still check
					if(!newTile->getPiece()){
						game->setPiece(newRow, newCol, currentTile->getPiece());
						game->setPiece(curRow, curCol, NULL);
						// check if it was a valid move:
						if(game->check(1)){ // swaps them back 
							game->setPiece(curRow, curCol, newTile->getPiece());
							game->setPiece(newRow, newCol, NULL);
							cout << "Invalid move, you are still in check! (Black)" << endl;
						}
					}
					// king /piece kills enemy piece
					// replace piece ptr to NULL while storing it in oppPiece, move our piece there
					// check for check
					// undo if still check: includes moving piece back and bringing it back
					// remember to kill piece if move is valid
					else{
						ChessPiece* oppPiece = newTile->getPiece(); 
						game->setPiece(newRow, newCol, currentTile->getPiece());
						game->setPiece(curRow, curCol, NULL);
						if(game->check(1)){ // if still in check, move pieces pack
							game->setPiece(curRow, curCol, newTile->getPiece());
							game->setPiece(newRow, newCol, oppPiece);
							cout << "Invalid move, you are still in check! (Black)" << endl;
						}
						else{ // it is a valid move, we must delete the piece and remove from player's pieces
							// if valid we must FIRST swap back, DELETE THEN MOVE cur piece to new tile
							game->setPiece(curRow, curCol, newTile->getPiece());
							game->setPiece(newRow, newCol, oppPiece);

							game->getPlayer(0)->removePiece(newTile);
							delete newTile->getPiece();
							// now assume piece is moving to empty square
							game->setPiece(newRow, newCol, currentTile->getPiece());
							game->setPiece(curRow, curCol, NULL);
						}
					}

					game->getPlayer(1)->setPiece(currentTile, newTile);
					updateViews();
					game->nextTurn();
					continue;// same as below 
				} 
			}
			// ***********************CHECK END ***************************
			// *********************** EN PASSANT BEGIN ******************************
			// en passant checks
			if(currentTile->getPiece()){ //if there is a chessPiece at the first coord
				// check to see if its a pawn
				if(currentTile->getPiece()->getType() == 'p' && game->getEnPassant() && !newTile->getPiece()){ 
					// BLACK pawn moves downwards, bot left or bot right
					// curRow < newRow BUT col could be less or greater
					if(curCol != newCol && game->getTile(newRow-1, newCol)->getPiece()->getType() == 'P'){ 
					// means pawn is moving diagonally
					// en passant used by BLACK
						game->setPiece(newRow, newCol, currentTile->getPiece());
						game->setPiece(curRow, curCol, NULL);
						delete game->getTile(newRow - 1, newCol)->getPiece();
						game->setPiece(newRow - 1, newCol, NULL);
						game->setEnPassant(false);

						game->getPlayer(1)->setPiece(currentTile, newTile);
						updateViews();
						game->nextTurn();
						continue;// same as below
					}
				}
				else if(currentTile->getPiece()->getType() == 'P' && game->getEnPassant() && !newTile->getPiece()){ 
					// White pawn moves upwards, top left or top right
					// curRow > newRow BUT col could be less or greater
					if(curCol != newCol && game->getTile(newRow + 1, newCol)->getPiece()->getType() == 'p'){ 
					// means pawn is moving diagonally
					// en passant used by BLACK
						game->setPiece(newRow, newCol, currentTile->getPiece());
						game->setPiece(curRow, curCol, NULL);
						delete game->getTile(newRow + 1, newCol)->getPiece();
						game->setPiece(newRow + 1, newCol, NULL);
						game->setEnPassant(false);

						game->getPlayer(0)->setPiece(currentTile, newTile);
						updateViews();
						game->nextTurn();
						continue;// same as below
					}
				}
			}
			// *********************** EN PASSANT END ********************************
			// *********************** PAWN PROMOTION BEGIN***************************
			// pawn promotion checks
			if(currentTile->getPiece()){ //if there is a chessPiece at the first coord
				// check to see if its a pawn
				if(currentTile->getPiece()->getType() == 'p' && newRow == 7){
					// pawn promotion happening for BLACK
					cin >> pieceType; // piece player wants for promotion
					game->promotePawn(curRow, curCol, newRow, newCol, pieceType, 'B'); // what fields are required here?

					game->getPlayer(1)->setPiece(currentTile, newTile);
					updateViews();
					game->nextTurn();
					continue;// same as below
				}
				else if(currentTile->getPiece()->getType() == 'P' && newRow == 0){
					// pawn promotion happening for WHITE
					cin >> pieceType; // piece player wants for promotion
					game->promotePawn(curRow, curCol, newRow, newCol, pieceType, 'W'); // what fields are required here?

					game->getPlayer(0)->setPiece(currentTile, newTile);
					updateViews();
					game->nextTurn();
					continue;// same as below
				}
			}

			// *********************** PAWN PROMOTION END***************************
			assert(game->getTurn());
			// Must set it to false HERE
			// this means no one has capitilized on the enPassant and 
			// it is now available to be set to true again
			game->setEnPassant(false);

			// ***********************REGULAR MOVE CHECK BEGIN ***************************
			// otherwise just move piece if possible
			if(game->getTurn() == 'W'){
				if(!game->getPlayer(0)->checkValid(curRow, curCol, newRow, newCol)){
					cout << "Invalid Move for  P1" << endl;
					// game->nextTurn();
					continue;
				}
				// valid move, check for capture, if not capturing, just moving piece to empty tile
				if(newTile->getPiece()){
					char type = newTile->getPiece()->getType();
					if(type >= 'a' && type <= 'z'){ // piece is black, we are white
						// delete it and replace all pointers to NULL
						game->getPlayer(1)->removePiece(newTile);
						delete newTile->getPiece();
						newTile->setPiece(NULL);
						game->getPlayer(0)->setPiece(currentTile, newTile);
					}
				}
			}
			else {
				if(!game->getPlayer(1)->checkValid(curRow, curCol, newRow, newCol)){
					cout << "Invalid Move for P2" << endl;
					// game->nextTurn();
					continue; 
				}
				// valid move, check for capture, if not capturing, just moving piece to empty tile
				if(newTile->getPiece()){
					char type = newTile->getPiece()->getType();
					if(type >= 'A' && type <= 'Z'){ // piece is white, we are black
						// delete it and replace all pointers to NULL
						game->getPlayer(0)->removePiece(newTile);
						delete newTile->getPiece();
						newTile->setPiece(NULL);
						game->getPlayer(1)->setPiece(currentTile, newTile);
					}
				}
			}
			// ***********************REGULAR MOVE CHECK END ***************************
			// ***********************MOVING NECESSARY PIECES BEGIN***************************
			// if the piece is just moving to an empty tile
			if(!newTile->getPiece()){
				game->setPiece(newRow, newCol, currentTile->getPiece());
				game->setPiece(curRow, curCol, NULL);
			}

			if(currentTile->getPiece()){ // update view based on empty space or piece
				viewNotify(curRow, curCol, currentTile->getPiece()->getType());
			}
			else{
				char c = ((curRow + curCol) % 2)? '-': ' ';
				viewNotify(curRow, curCol, c);
			}
			if(newTile->getPiece()){ // update view based on empty space or piece
				viewNotify(newRow, newCol, newTile->getPiece()->getType());
			}
			else{
				char c = ((newRow + newCol) % 2)? '-': ' ';
				viewNotify(newRow, newCol, c);
			}
			// ***********************MOVING NECESSARY PIECES END***************************
			// check and Checkmate
			if(game->check(0)){
				cout << "White is in check" << endl;
				if(game->checkmate(0)){
					cout << "Checkmate! Black wins!" << endl;
					game->nextTurn();
					resign();
					continue;
				}
			}
			else{
				if(game->stalemate(0)){
				cout << "White is in stalemate, it is a draw." << endl;
				}
			}

			if(game->check(1)){
				cout << "Black is in check" << endl;
				if(game->checkmate(1)){
					cout << "Checkmate! White wins!" << endl;
					game->nextTurn();
					resign();
					continue;
				}
			}
			else{
				if(game->stalemate(1)){
				cout << "Black is in stalemate, it is a draw." << endl;
				}
			}
			game->getPlayer(0)->setPiece(currentTile, newTile);
			game->nextTurn();
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
					int curRow = rowToIndex(location.at(1) - '0');
					int curCol = colToIndex(location.at(0));
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
					int curRow = rowToIndex(location.at(1));
					int curCol = colToIndex(location.at(0));

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
				updateViews();
			}
		}
		updateViews();
	}
}
