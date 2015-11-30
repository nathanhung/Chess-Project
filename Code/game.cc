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
