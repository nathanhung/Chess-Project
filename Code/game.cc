#include "game.h"
#include <cassert>
#include "player.h"
#include "human.h"
#include "CPU.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "controller.h"
Game::Game(int n, Controller& controller,string p1, string p2, char turn): GRIDSIZE(n), controller(controller), turn(turn), enPassant(false) {

	// player1
	// if human
	if (p1 == "human"){
		players[0] = new Human(0, this);
	} 
	// otherwise its a CPU
	else {
		int level = p1.at(8) - '0';
		players[0] = new CPU(0, level, this);
	}

	// player2
	// if human
	if (p2 == "human"){
		players[1] = new Human(1, this);
	} 
	// otherwise its a CPU
	else { // we have computer1
		int level = p2.at(8) - '0';
		players[1] = new CPU(1, level, this);
	}

	// setup theGrid
	theGrid = new Tile* [GRIDSIZE];
  	for(int i = 0; i < GRIDSIZE; ++i){
	    theGrid[i] = new Tile[GRIDSIZE];
	    // setup the row indices
	    for(int j = 0; j < GRIDSIZE; j++){
	    	// do first row
	    	if(i == 0){
	    		if(j == 0 || j == 7){
	    			theGrid[i][j].setPiece(new Rook('B','r', this));
	    		}
	    		else if(j == 1 || j == 6){
	    			theGrid[i][j].setPiece(new Knight('B','n', this));
	    		}
	    		else if(j == 2 || j == 5){
	    			theGrid[i][j].setPiece(new Bishop('B','b', this));
	    		}
	    		else if(j == 3){
	    			theGrid[i][j].setPiece(new Queen('B','q', this));
	    		}
	    		else{
	    			theGrid[i][j].setPiece(new King('B','k', this));
	    			players[0]->setKing1(&theGrid[i][j]);
	    			players[1]->setKing2(&theGrid[i][j]);
	    		}
	    		players[1]->addPiece(&theGrid[i][j]);
	    	}

	    	// do second row
	    	else if(i == 1){
	    		theGrid[i][j].setPiece(new Pawn('B','p', this));
	    		players[1]->addPiece(&theGrid[i][j]);
	    	}

	    	// seventh row
	    	else if(i == 6){
	    		theGrid[i][j].setPiece(new Pawn('W','P', this));
	    		players[0]->addPiece(&theGrid[i][j]);
	    	}

	    	// eigth row	
	    	else if(i == 7){
	    		if(j == 0 || j == 7){
	    			theGrid[i][j].setPiece(new Rook('W', 'R', this));
	    		}
	    		else if(j == 1 || j == 6){
	    			theGrid[i][j].setPiece(new Knight('W', 'N', this));
	    		}
	    		else if(j == 2 || j == 5){
	    			theGrid[i][j].setPiece(new Bishop('W', 'B', this));
	    		}
	    		else if(j == 3){
	    			theGrid[i][j].setPiece(new King('W', 'K', this));
	    			players[0]->setKing1(&theGrid[i][j]);
	    			players[1]->setKing2(&theGrid[i][j]);
	    		}
	    		else{
	    			theGrid[i][j].setPiece(new Queen('W', 'Q', this));
	    		}
	    		players[0]->addPiece(&theGrid[i][j]);
	    	}
	    	theGrid[i][j].setGame(this);
	    	theGrid[i][j].setCoords(i, j);
    	}
  } 	
}

Game::~Game(){
	for(int i = 0 ; i < GRIDSIZE; i++){
		delete [] theGrid[i];
	}
	delete theGrid;
}

void Game::setPlayer(Player* p, int index){
	players[index];
}

char Game::getTurn(){
	return turn;
}

void Game::setTurn(char turn){
	turn = turn;
}

Player* Game::getPlayer(int n){
	assert(players);
	return players[n];
}

void Game::promotePawn(int row, int col, char pieceType){
	theGrid[row][col].getPiece()->setType(pieceType);
}

void Game::swapTiles(Tile* currentTile, Tile* newTile){
	
}

Tile* Game::getTile(int row, int col){
	return &theGrid[row][col];
}

void Game::setPiece(int row, int col, ChessPiece* piece){
	getTile(row, col)->setPiece(piece);
}

bool Game::checkBoard(){
	Player* p1 = getPlayer(0);
	Player* p2 = getPlayer(1);
	int pieces1 = p1->getNumPieces();
	int pieces2 = p2->getNumPieces();

	// more than 1 king
	int wKings = 0;
	int bKings = 0;
	for(int i = 0; i < pieces1; i++){
		if(p1->getPiece(i)->getPiece()->getType() == 'K'){
			wKings++;
		}
	}
	for(int i = 0; i < pieces2; i++){
		if(p2->getPiece(i)->getPiece()->getType() == 'k'){
			bKings++;
		}
	}
	if(wKings > 1 || bKings > 1){
		return false;
	}
	// pawns in unplaceable spots
	for(int i = 0; i < 8; i++){
		// check first row for 'p'
		if(getTile(0, i)->getPiece()->getType() == 'p'){
			return false;
		}
		// check seventh row for 'P'
		if(getTile(7, i)->getPiece()->getType() == 'P'){
			return false;
		}
	}
	// if all tests pass, return true
	return true;
}

void Game::notifierNotify(int row, int col, char piece){
	controller.viewNotify(row, col, piece);
}

bool Game::getEnPassant(){
	return enPassant;
}

Tile** Game::getGrid(){
	return theGrid;
}
