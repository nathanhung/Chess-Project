#ifndef CHESSPIECE_H
#define CHESSPIECE_H
class Player;

class ChessPiece {
	Player* owner;
	char type;
public:
	ChessPiece(char type);
	virtual ~ChessPiece() = 0;
	virtual bool checkMove(int curRow, int curCol, int newRow, int newCol) = 0;
};
#endif
