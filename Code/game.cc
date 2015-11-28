// remember to destroy all the tiles too.
class Game {
	char turn; // 'W' = player1's turn, 'B' = player2's turn
	Tile** theGrid;
	const int GRIDSIZE;
	Controller& controller; // change this to gameNotification?
	Player* players;

	Game(int n, Controller& controller, Player* p1, Player* p2, char turn);
	virtual ~Game() = 0;
};

Game::Game(int n, Controller& controller, Player* p1, Player* p2, char turn): GRIDSIZE(n), controller(controller){
	players = new Player[2];
	players[0] = p1;
	players[1] = p2;

	// setup theGrid
	Tile** arr = new Tile* [GRIDSIZE];
  	for(int i = 0; i < GRIDSIZE; ++i){
	    arr[i] = new Tile[GRIDSIZE](this);
	    // setup the row indices
	    for(int j = 0; j < GRIDSIZE; j++){
	    	// do first row
	    	if(i == 0){
	    		if(j == 1 || j == 8){
	    			arr[i][j]->chessPiece('r');
	    		}
	    		else if(j == 2 || j == 7){
	    			arr[i][j]->piece('n');
	    		}
	    		else if(j == 3 || j == 6){
	    			arr[i][j]->piece('b');
	    		}
	    		else if(j == 4){
	    			arr[i][j]->piece('q');
	    		}
	    		else{
	    			arr[i][j]->piece('k');
	    		}
	    	}

	    	// do second row
	    	else if(i == 1){
	    		arr[i][j]->piece('p');
	    	}

	    	// seventh row
	    	else if(i == 6){
	    		arr[i][j]->piece('P');
	    	}
	    	// eigth row	
	    	else if(i == 7){
	    		if(j == 1 || j == 8){
	    			arr[i][j]->piece('R');
	    		}
	    		else if(j == 2 || j == 7){
	    			arr[i][j]->piece('N');
	    		}
	    		else if(j == 3 || j == 6){
	    			arr[i][j]->piece('B');
	    		}
	    		else if(j == 4){
	    			arr[i][j]->piece('K');
	    		}
	    		else{
	    			arr[i][j]->piece('Q');
	    		}
	    	}
    	}
  }
  theDisplay = arr;
}
