#include "chesspiece.h"

ChessPiece::ChessPiece(char owner, char type, Game* game): owner(owner), type(type), game(game) {}

ChessPiece::~ChessPiece() {}

char ChessPiece::getType(){
	return type;
}

void ChessPiece::setType(char pieceType){
	type = pieceType;
}
