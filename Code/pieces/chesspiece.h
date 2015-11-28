#ifndef CHESSPIECE_H
#define CHESSPIECE_H
class Player;

class ChessPiece {
	Player* owner;
	char type;
public:
	ChessPiece(char type);
	virtual ~ChessPiece();
};
#endif
