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

Game::~Game(){
	for(int i = 0 ; i < GRIDSIZE; i++){
		delete [] theGrid[i];
	}
	delete theGrid;
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

bool reachable(int kingRow, int kingCol, int newRow, int newCol, Player* p, Player* opponent){
	if(newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7){
		return false;
	}

	if(p->checkValid(kingRow, kingCol, newRow, newCol)){ // check if this spot is reachale by ANY of enemy's pieces
		bool reachable = false;
		for(int i = 0; i < opponent->getNumPieces(); i++){
			int curRow = opponent->getPiece(i)->getRow();
			int curCol = opponent->getPiece(i)->getColumn();
			if(opponent->checkValid(curRow, curCol, newRow, newCol)){
				reachable = true;
			}
		}
		if(!reachable){
			return false;
		}
	}

	return true;
}

bool Game::checkmate(int index){ // index of player, 0 = W, 1 = B
	// if check we can check if King can move to a spot where the enemy cant
	if(!check(index)){
		return false;
	}
	// get current Index's king, so we can get its pos
	Player* p = players[index];
	Player* opponent = (index)? players[0] : players[1];
	Tile* kingTile = (index)? p->getKing2() : p->getKing1();

	int kingRow = kingTile->getRow();
	int kingCol = kingTile->getColumn();

	// go through every MOVEABLE spot the king can go to, 8 possibilities
	// see if:
	// 1. King can go to that spot (valid spot, empty or enemy piece)
	// 2. Any enemy piece's can go there
	// 3. If we've found a spot where King can go and enemy pieces can't, false
	// 4. otherwise true

	// we can call this player's checkvalid on this King for all 8 combinations
	if(!reachable(kingRow, kingCol, kingRow - 1, kingCol -1, p, opponent )){ // -1 -1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow, kingCol -1, p, opponent )){ // 0 -1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow - 1, kingCol, p, opponent )){ // -1 0
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow + 1, kingCol + 1, p, opponent )){ // +1 +1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow, kingCol + 1, p, opponent )){ // 0 +1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow + 1, kingCol, p, opponent )){ // +1 0
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow - 1, kingCol  +1, p, opponent )){ // -1 +1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow + 1, kingCol  - 1, p, opponent )){ // +1 -1
		return false;
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
	Player* opponent = (index)? players[0] : players[1];
	Tile* kingTile = (index)? p->getKing2() : p->getKing1();

	int kingRow = kingTile->getRow();
	int kingCol = kingTile->getColumn();

	// go through every MOVEABLE spot the king can go to, 8 possibilities
	// see if:
	// 1. King can go to that spot (valid spot, empty or enemy piece)
	// 2. Any enemy piece's can go there
	// 3. If we've found a spot where King can go and enemy pieces can't, false
	// 4. otherwise true

	// we can call this player's checkvalid on this King for all 8 combinations
	if(!reachable(kingRow, kingCol, kingRow - 1, kingCol -1, p, opponent )){ // -1 -1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow, kingCol -1, p, opponent )){ // 0 -1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow - 1, kingCol, p, opponent )){ // -1 0
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow + 1, kingCol + 1, p, opponent )){ // +1 +1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow, kingCol + 1, p, opponent )){ // 0 +1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow + 1, kingCol, p, opponent )){ // +1 0
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow - 1, kingCol  +1, p, opponent )){ // -1 +1
		return false;
	}
	if(!reachable(kingRow, kingCol, kingRow + 1, kingCol  - 1, p, opponent )){ // +1 -1
		return false;
	}

	return true;

}
void Game::nextTurn(){
	turn = (turn == 'W')? 'B':'W';
}
