#include "game.h"

Game::Game(int n, Controller& controller, Player* p1, Player* p2, char turn): GRIDSIZE(n), controller(controller){
	players[0] = p1;
	players[1] = p2;

	// setup theGrid
	Tile** arr = new Tile* [GRIDSIZE];
  	for(int i = 0; i < GRIDSIZE; ++i){
	    arr[i] = new Tile[GRIDSIZE];
	    // setup the row indices
	    for(int j = 0; j < GRIDSIZE; j++){
	    	// do first row
	    	if(i == 0){
	    		if(j == 1 || j == 8){
	    			arr[i][j].setPiece(new ChessPiece('r'));
	    		}
	    		else if(j == 2 || j == 7){
	    			arr[i][j].setPiece(new ChessPiece('n'));
	    		}
	    		else if(j == 3 || j == 6){
	    			arr[i][j].setPiece(new ChessPiece('b'));
	    		}
	    		else if(j == 4){
	    			arr[i][j].setPiece(new ChessPiece('q'));
	    		}
	    		else{
	    			arr[i][j].setPiece(new ChessPiece('k'));
	    		}
	    		players[1]->addPiece(arr[i][j]);
	    	}

	    	// do second row
	    	else if(i == 1){
	    		arr[i][j].setPiece(new ChessPiece('p'));
	    		players[1]->addPiece(arr[i][j]);
	    	}

	    	// seventh row
	    	else if(i == 6){
	    		arr[i][j].setPiece(new ChessPiece('P'));
	    		players[0]->addPiece(arr[i][j]);
	    	}

	    	// eigth row	
	    	else if(i == 7){
	    		if(j == 1 || j == 8){
	    			arr[i][j].setPiece(new ChessPiece('R'));
	    		}
	    		else if(j == 2 || j == 7){
	    			arr[i][j].setPiece(new ChessPiece('N'));
	    		}
	    		else if(j == 3 || j == 6){
	    			arr[i][j].setPiece(new ChessPiece('B'));
	    		}
	    		else if(j == 4){
	    			arr[i][j].setPiece(new ChessPiece('K'));
	    		}
	    		else{
	    			arr[i][j].setPiece(new ChessPiece('Q'));
	    		}
	    		players[0]->addPiece(arr[i][j]);
	    	}
	    	arr[i][j].setGame(this);
	    	arr[i][j].setCoords(i, j);
    	}
  }
  theGrid = arr;

  players[0]->setGrid(theGrid);
  players[1]->setGrid(theGrid);
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
