#ifndef CHESSPIECE_H
#define CHESSPIECE_H
class Game;

class ChessPiece {
protected:
	char type;
	Game* game;
	char owner;
public:
	ChessPiece(char owner, char type, Game* game); //ctor
	virtual ~ChessPiece();
	virtual bool checkMove(int curRow, int curCol, int newRow, int newCol) = 0;
	char getType();
	void setType(char pieceType);
	virtual bool getCastling();
	virtual void setCastling();
};

#endif
