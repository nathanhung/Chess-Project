#ifndef CHESSPIECE_H
#define CHESSPIECE_H
class Player;

class ChessPiece {
	Player* owner;
	char type;

	ChessPiece(char type);
	virtual ~ChessPiece() = 0;
};
#endif
