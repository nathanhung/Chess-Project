#include "chesspiece.h"

ChessPiece::ChessPiece(char owner, char type, game* game): owner(owner), type(type), game(game) {}

ChessPiece::~ChessPiece(){}
