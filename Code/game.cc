#include "game.h"

Game::Game(int n, Controller& controller,string p1, string p2, char turn): GRIDSIZE(n), controller(controller){

	// player1
	// if human
	if (p1 == "human"){
		players[0] = new Human();
	} 
	// otherwise its a CPU
	else {
		int level = p1.at(8) - '0';
		players[0] = new CPU(level);
	}

	// player2
	// if human
	if (p2 == "human"){
		players[1] = new Human();
	} 
	// otherwise its a CPU
	else { // we have computer1
		int level = p2.at(8) - '0';
		players[1] = new CPU(level);
	}
  	players[0]->setGrid(theGrid);
  	players[1]->setGrid(theGrid);


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
	    			players[0]->setKing1(arr[i][j]);
	    			players[1]->setKing2(arr[i][j]);
	    		}
	    		players[1]->addPiece(arr[i][j]);
	    	}

	    	// do second row
	    	else if(i == 1){
	    		arr[i][j].setPiece(new Pawn('B','p', this));
	    		players[1]->addPiece(arr[i][j]);
	    	}

	    	// seventh row
	    	else if(i == 6){
	    		arr[i][j].setPiece(new Pawn('W','P', this));
	    		players[0]->addPiece(arr[i][j]);
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
	    			players[0]->setKing1(arr[i][j]);
	    			players[1]->setKing2(arr[i][j]);
	    		}
	    		else{
	    			arr[i][j].setPiece(new Queen('W', 'Q', this));
	    		}
	    		players[0]->addPiece(arr[i][j]);
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

Player* Game::getPlayer(int n){
	assert(players);
	return players[n];
}

void Game::promotePawn(int row, int col, char pieceType){
	theGrid[row][col]->getPiece()->setType(pieceType);
}
