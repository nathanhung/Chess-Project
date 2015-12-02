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
Game::Game(int n, Controller& controller,string p1, string p2, char turn): GRIDSIZE(n), controller(controller), turn(turn){

	// player1
	// if human
	if (p1 == "human"){
		players[0] = new Human(0);
	} 
	// otherwise its a CPU
	else {
		int level = p1.at(8) - '0';
		players[0] = new CPU(0, level);
	}

	// player2
	// if human
	if (p2 == "human"){
		players[1] = new Human(1);
	} 
	// otherwise its a CPU
	else { // we have computer1
		int level = p2.at(8) - '0';
		players[1] = new CPU(1, level);
	}
  	players[0]->setGame(this);
  	players[1]->setGame(this);


	// setup theGrid
	Tile** arr = new Tile* [GRIDSIZE];
  	for(int i = 0; i < GRIDSIZE; ++i){
	    arr[i] = new Tile[GRIDSIZE];
	    // setup the row indices
	    for(int j = 0; j < GRIDSIZE; j++){
	    	// do first row
	    	if(i == 0){
	    		if(j == 0 || j == 7){
	    			arr[i][j].setPiece(new Rook('B','r', this));
	    		}
	    		else if(j == 1 || j == 6){
	    			arr[i][j].setPiece(new Knight('B','n', this));
	    		}
	    		else if(j == 2 || j == 5){
	    			arr[i][j].setPiece(new Bishop('B','b', this));
	    		}
	    		else if(j == 3){
	    			arr[i][j].setPiece(new Queen('B','q', this));
	    		}
	    		else{
	    			arr[i][j].setPiece(new King('B','k', this));
	    			players[0]->setKing1(&arr[i][j]);
	    			players[1]->setKing2(&arr[i][j]);
	    		}
	    		players[1]->addPiece(&arr[i][j]);
	    	}

	    	// do second row
	    	else if(i == 1){
	    		arr[i][j].setPiece(new Pawn('B','p', this));
	    		players[1]->addPiece(&arr[i][j]);
	    	}

	    	// seventh row
	    	else if(i == 6){
	    		arr[i][j].setPiece(new Pawn('W','P', this));
	    		players[0]->addPiece(&arr[i][j]);
	    	}

	    	// eigth row	
	    	else if(i == 7){
	    		if(j == 0 || j == 7){
	    			arr[i][j].setPiece(new Rook('W', 'R', this));
	    		}
	    		else if(j == 1 || j == 6){
	    			arr[i][j].setPiece(new Knight('W', 'N', this));
	    		}
	    		else if(j == 2 || j == 5){
	    			arr[i][j].setPiece(new Bishop('W', 'B', this));
	    		}
	    		else if(j == 3){
	    			arr[i][j].setPiece(new King('W', 'K', this));
	    			players[0]->setKing1(&arr[i][j]);
	    			players[1]->setKing2(&arr[i][j]);
	    		}
	    		else{
	    			arr[i][j].setPiece(new Queen('W', 'Q', this));
	    		}
	    		players[0]->addPiece(&arr[i][j]);
	    	}
	    	arr[i][j].setGame(this);
	    	arr[i][j].setCoords(i, j);
    	}
  }
  theGrid = arr;  	
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
	int curRow = currentTile->getRow();
	int curCol = currentTile->getColumn();

	int newRow = newTile->getRow();
	int newCol = newTile->getColumn();
	
	Tile* temp = currentTile;
	theGrid[curRow][curCol] = *newTile;
	theGrid[newRow][newCol] = *temp;
}

Tile* Game::getTile(int row, int col){
	return &theGrid[row][col];
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
