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
#include <fstream>
#include <iostream>
using namespace std;

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
  	for(int i = 0; i < GRIDSIZE; i++){
	    theGrid[i] = new Tile[GRIDSIZE];
	    // setup the row indices
	    for(int j = 0; j < GRIDSIZE; j++){

	    	theGrid[i][j].setGame(this);
	    	theGrid[i][j].setCoords(i, j);
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
	    			players[0]->setKing2(&theGrid[i][j]);
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
	    			theGrid[i][j].setPiece(new Queen('W', 'Q', this));
	    		}
	    		else{
	    			theGrid[i][j].setPiece(new King('W', 'K', this));
	    			players[0]->setKing1(&theGrid[i][j]);
	    			players[1]->setKing1(&theGrid[i][j]);
	    		}
	    		players[0]->addPiece(&theGrid[i][j]);
	    	}
    	}
    }
}

Game::Game(int n, Controller& controller, string filename): GRIDSIZE(n), controller(controller), enPassant(false) {
	ifstream file(filename.c_str());

	if(!file.good()){
		cout << "File not found!" << endl;
	}

	char piece;
	char owner;
	ChessPiece* cp;

	theGrid = new Tile* [GRIDSIZE];
  	for(int i = 0; i < GRIDSIZE; i++){
	    theGrid[i] = new Tile[GRIDSIZE];
	    // setup the row indices
	    for(int j = 0; j < GRIDSIZE; j++){

	    	theGrid[i][j].setGame(this);
	    	theGrid[i][j].setCoords(i, j);
	    	file >> piece;
	    	cout << "Piece: " << piece << endl;
	    	// piece type check
	    	if(piece == 'p' || piece + 32 == 'p'){
				cp = new Pawn('W', piece, this);
			}
			// Bishop
			else if(piece == 'b' || piece + 32 == 'b'){
				cp = new Bishop('W', piece, this);
			}
			// Rook
			else if(piece == 'r' || piece + 32 == 'r'){
				cp = new Rook('W', piece, this);
			}
			// Queen
			else if(piece == 'q' || piece + 32 == 'q'){
				cp = new Queen('W', piece, this);
			}
			// King
			else if(piece == 'k' || piece + 32 == 'k'){
				cp = new King('W', piece, this);
			}
			// Knight
			else if(piece == 'n' || piece + 32 == 'n'){
				cp = new Knight('W', piece, this);
			}
			// empty piece
			else if(piece == '_'){
				continue;
			}
			// else ERROR
			else{
				cout << "INVALID PIECE TYPE IN FILE READ MODE!" << endl;
				continue;
			}
			theGrid[i][j].setPiece(cp);
			theGrid[i][j].getPiece()->getType();
		}
		//file.ignore();
		
	}
	// made grid, get turn
		file >> piece;
		turn = piece;

		cout << turn << endl;
		// get types of player's and set their pieces
		string p1, p2;
		cin >> p1 >> p1 >> p2; // scrap "game" word

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

		for(int i = 0; i < GRIDSIZE; i++){
			for(int j = 0; j < GRIDSIZE; j++){
				char c = ' ';
				if(theGrid[i][j].getPiece()){
					c = theGrid[i][j].getPiece()->getType();
				}
				if(c == 'K'){
					players[0]->setKing1(&theGrid[i][j]);
					players[1]->setKing1(&theGrid[i][j]);
				}
				else if(c == 'k'){
					players[0]->setKing2(&theGrid[i][j]);
					players[1]->setKing2(&theGrid[i][j]);
				}
				if(c >= 'A' && c <= 'Z'){ // White's piece
					players[0]->addPiece(&theGrid[i][j]);
				}
				else if(c >= 'a' && c <= 'z'){ // Black's piece
					players[1]->addPiece(&theGrid[i][j]);
				}
				else{
					continue;
				}
			}
		}
		// check for castling
		//controller.updateViews(); 
		controller.updateFromFile(theGrid);
}

Game::~Game(){
	for(int i = 0 ; i < GRIDSIZE; i++){
		delete [] theGrid[i];
	}
	delete  [] theGrid;

	delete players[0];
	delete players[1];
	players[0] = NULL;
	players[1] = NULL;

	controller.makeViews();
}

void Game::setPlayer(Player* p, int index){
	players[index] = p;
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

void Game::promotePawn(int curRow, int curCol, int newRow, int newCol, char pieceType, char owner){
	// set new position to new piece of type pieceType
	// set cur pos to NULL
	delete theGrid[curRow][curCol].getPiece();
	theGrid[curRow][curCol].setPiece(NULL);

	ChessPiece* newPiece;
	if(pieceType == 'q' || pieceType + 32 == 'q'){
		newPiece = new Queen(owner, pieceType, this);
	}
	else if(pieceType == 'b' || pieceType + 32 == 'b'){
		newPiece = new Bishop(owner, pieceType, this);
	}
	else if(pieceType == 'r' || pieceType + 32 == 'r'){
		newPiece = new Rook(owner, pieceType, this);
	}
	else if(pieceType == 'n' || pieceType + 32 == 'n'){
		newPiece = new Knight(owner, pieceType, this);
	}
	else{
		cout << "Invalid Piece type, cannot promote!" << endl;
	}
	theGrid[newRow][newCol].setPiece(newPiece);
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

void Game::setEnPassant(bool value){
	enPassant = value;
}

Tile** Game::getGrid(){
	return theGrid;
}

bool Game::check(int index){ //index 0 = W, 1 = B
	Player* p = players[index];
	Player* opponent = (index)? players[0] : players[1];
	Tile* kingTile = (index)? p->getKing2() : p->getKing1();

	int kingRow = kingTile->getRow();
	int kingCol = kingTile->getColumn();

	// we have this player's position, now check if OPPOSITE player's
	// pieces can reach THIS player's king
	for(int i = 0; i < opponent->getNumPieces(); i++){
		int curRow = opponent->getPiece(i)->getRow();
		int curCol = opponent->getPiece(i)->getColumn();
		// cout << kingRow<< kingCol << endl;

		// cout <<"PIECE POS: "<< curRow << curCol << endl;
		// cout << "KING POS "<< kingRow << kingCol << endl;

		if(opponent->checkValid(curRow, curCol, kingRow, kingCol)){
			return true;
		}
	}
	return false;
}

// bool reachable(int kingRow, int kingCol, int newRow, int newCol, Player* p, Player* opponent){
// 	if(newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7){
// 		return true;
// 	}

// 	if(p->checkValid(kingRow, kingCol, newRow, newCol)){ // check if this spot is reachale by ANY of enemy's pieces
// 		bool reachable = false;
// 		for(int i = 0; i < opponent->getNumPieces(); i++){
// 			int curRow = opponent->getPiece(i)->getRow();
// 			int curCol = opponent->getPiece(i)->getColumn();
// 			if(opponent->checkValid(curRow, curCol, newRow, newCol)){
// 				reachable = true;
// 			}
// 		}
// 		if(!reachable){
// 			return false;
// 		}
// 	}

// 	return true;
// }

bool Game::checkmate(int index){ // index of player, 0 = W, 1 = B
	// if check we can check if King can move to a spot where the enemy cant
	if(!check(index)){ // basic check
		cout << "Not in check!" << endl;
		return false;
	}
	// get current Index's king, so we can get its pos
	Player* p = players[index];
	//Player* opponent = (index)? players[0] : players[1];

	// go through every spot on the board and see if this player's piece can go there
	// see if:
	// 1. for every tile on the board
	// 2. see if this player can move to any of those spots with its pieces
	// 3. If for all the possible moves we are STILL in check, return true
	// 4. otherwise if we found a possible move that takes us out of check return false
	for(int i = 0; i < GRIDSIZE; i++){ // 1.
		for(int j = 0; j < GRIDSIZE; j++){
			for(int k = 0; k < p->getNumPieces(); k++){ // 2.
				int curRow = p->getPiece(k)->getRow();
				int curCol = p->getPiece(k)->getColumn();
				if(p->checkValid(curRow, curCol, i, j)){ // 3.
					if(!stillInCheck(curRow, curCol, i, j)){
						cout << "Found possible move!" << curRow << curCol << i << j << turn<< endl;
						return false;
					}
				}
			}
		}
	}
	return true;
}

// only difference with checkmate is that person is NOT in check
bool Game::stalemate(int index){// index of player, 0 = W, 1 = B
	// if check we can check if King can move to a spot where the enemy cant
	if(check(index)){ // this will be assumed but just in case
		return false;
	}
	// get current Index's king, so we can get its pos
	Player* p = players[index];
	//Player* opponent = (index)? players[0] : players[1];
	// Tile* kingTile = (index)? p->getKing2() : p->getKing1();

	// go through every spot on the board and see if this player's piece can go there
	// see if:
	// 1. for every tile on the board
	// 2. see if this player can move to any of those spots with its pieces
	// 3. If we've found a spot where that is reachable by at least one piece of this player AND doesn't put us in check
	// 4. return false
	// 5. if not false YET, double check to see if king can go there
	for(int i = 0; i < GRIDSIZE; i++){ // 1.
		for(int j = 0; j < GRIDSIZE; j++){
			for(int k = 0; k < p->getNumPieces(); k++){ // 2.
				int curRow = p->getPiece(k)->getRow();
				int curCol = p->getPiece(k)->getColumn();
				if(p->checkValid(curRow, curCol, i, j)){ // 3.
					if(!stillInCheck(curRow, curCol, i, j)){
						return false; 
					}
				}
			}
		}
	}
	return true;
}

void Game::nextTurn(){
	turn = (turn == 'W')? 'B':'W';
}

bool Game::stillInCheck(int curRow, int curCol, int newRow, int newCol){
	Tile* currentTile = getTile(curRow, curCol);
	Tile* newTile = getTile(newRow, newCol);
	//bool stillCheck = true; // assume player was in check from the beggining
	// after making this move, would the player still be in check?
	if(getTurn() == 'B'){ // white in check, turn check not necessary here but precautionary
		// check to see if the move they're trying to make will take them out of check
		if(getPlayer(0)->checkValid(curRow, curCol, newRow, newCol)){ // move is valid
			// cases
			// king / piece moves to an empty square
			// move it there, check for check then undo if still check
			if(!newTile->getPiece()){
				setPiece(newRow, newCol, currentTile->getPiece());
				setPiece(curRow, curCol, NULL);
				// check if it was a valid move:
				 // swaps them back 
				
				if(check(0)){
					cout << "Invalid move, you will still be in check! (White)" << endl;
				}
				setPiece(curRow, curCol, newTile->getPiece());
				setPiece(newRow, newCol, NULL);

				if(check(0)){
					return true;
				}

			}
			// king /piece kills enemy piece
			// replace piece ptr to NULL while storing it in oppPiece, move our piece there
			// check for check
			// undo if still check: includes moving piece back and bringing it back
			// remember to kill piece if move is valid
			else{
				ChessPiece* oppPiece = newTile->getPiece(); 
				setPiece(newRow, newCol, currentTile->getPiece());
				setPiece(curRow, curCol, NULL);
				
				if(check(0)){
					cout << "Invalid move, you will still be in check! (White)" << endl;
				}
				setPiece(curRow, curCol, newTile->getPiece());
				setPiece(newRow, newCol, oppPiece);

				if(check(0)){
					return true;
				}
			}
		} 
	}

	if(getTurn() == 'W'){ // white in check, turn check not necessary here but precautionary
		// check to see if the move they're trying to make will take them out of check
		if(getPlayer(1)->checkValid(curRow, curCol, newRow, newCol)){ // move is valid
			// cases
			// king / piece moves to an empty square
			// move it there, check for check then undo if still check
			if(!newTile->getPiece()){
				setPiece(newRow, newCol, currentTile->getPiece());
				setPiece(curRow, curCol, NULL);
				// check if it was a valid move:
				 // swaps them back
				
				if(check(0)){
					cout << "Invalid move, you will still be in check! (Black)" << endl;
				}
				setPiece(curRow, curCol, newTile->getPiece());
				setPiece(newRow, newCol, NULL);

				if(check(1)){
					return true;
				}
			}
			// king /piece kills enemy piece
			// replace piece ptr to NULL while storing it in oppPiece, move our piece there
			// check for check
			// undo if still check: includes moving piece back and bringing it back
			// remember to kill piece if move is valid
			else{
				ChessPiece* oppPiece = newTile->getPiece(); 
				setPiece(newRow, newCol, currentTile->getPiece());
				setPiece(curRow, curCol, NULL);

				if(check(1)){
					cout << "Invalid move, you will still be in check! (Black)" << endl;
				}

				setPiece(curRow, curCol, newTile->getPiece());
				setPiece(newRow, newCol, oppPiece);

				if(check(1)){
					return true;
				}
			}
		} 
	}
	return false;
}
