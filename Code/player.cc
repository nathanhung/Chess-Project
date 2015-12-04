#include "player.h"
#include "tile.h"
#include "pieces/chesspiece.h"
#include <cstdlib>
#include "game.h"
#include <cassert>
#include <iostream>
using namespace std;

Player::Player(int number, Game* game): game(game), numPieces(0), king1(NULL), king2(NULL), playerNumber(number){
	for(int i = 0; i < 16; i++){
		pieces[i] = NULL;
	}
}
Player::~Player(){}

void Player::setGame(Game* game){
	game = game;
}

void Player::addPiece(Tile* piece){
	pieces[numPieces] = piece;
	numPieces++;
}

void Player::setKing1(Tile* king){
	king1 = king;
}

void Player::setKing2(Tile* king){
	king2 = king;
}

Tile* Player::getKing1(){
	return king1;
}

Tile* Player::getKing2(){
	return king2;
}
// gets a piece from pieces array
Tile* Player::getPiece(int index){
	return pieces[index];
}

void Player::setPiece(Tile* oldTile, Tile* newTile){
	for(int i = 0; i < numPieces; i++){
		if(pieces[i] == oldTile){
			pieces[i] = newTile;
			return;
		}
	}
}

void Player::removePiece(Tile* tile){
	// find tile in our pieces array, and shift to left, deleting happens in cont
	int i;
	for(i = 0; i < numPieces; i++){
		if(tile == pieces[i]){
			break;
		}
	}
	for(; i < numPieces - 1; i++){
		pieces[i] = pieces[i+1];
	}
	numPieces--;
}

int Player::getNumPieces(){
	return numPieces;
}
// checks if move is possible based on current position and desired position
bool Player::checkValid(int curRow, int curCol, int newRow, int newCol){

	// cout <<"PIECE POS: "<< curRow << curCol << endl;
	// cout << "NEW POS "<< newRow << newCol << endl;

	assert(newRow > -1 && newRow < 8);
	assert(newCol > -1 && newCol < 8);
	// find the tile at cur
	Tile* currentTile = game->getTile(curRow, curCol);
	Tile* newTile = game->getTile(newRow, newCol);
	
	// ASSUME IT IS THIS PLAYER'S PIECE AND HE HAS THE POWER TO MOVE IT
	// check if new position is empty or has an enemy piece
	// or more simply, return false if the new pos is our OWN piece
	char pieceType;
	if(newTile->getPiece()){
		pieceType = newTile->getPiece()->getType();

		// check for player's own pieces at new spot
		if(playerNumber == 0 && (pieceType >= 'A' && pieceType <= 'Z')) {
			return false;
		}
		if(playerNumber == 1 && (pieceType >= 'a' && pieceType <= 'z')) {
			return false;
		}
	}

	
	
	// check if piece at cur can move to new tile
	// if(currentTile->getPiece()){
	// 	cout << "Current Piece: "<< currentTile->getPiece()->getType() << endl;
	// }
	if(!currentTile->getPiece()){
		//cout << "No Piece!" << endl;
		return false;
	}	
	return currentTile->getPiece()->checkMove(curRow, curCol, newRow, newCol);
}
