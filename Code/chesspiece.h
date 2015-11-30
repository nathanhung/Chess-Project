#ifndef CHESSPIECE_H
#define CHESSPIECE_H
class Game;

class ChessPiece {
	char owner;
	char type;
<<<<<<< HEAD:Code/pieces/chesspiece.h
	Game* game;
	public:
		ChessPiece(char owner, char type); //ctor
		virtual ~ChessPiece() = 0;
		virtual bool checkMove(int curRow, int curCol, int newRow, int newCol) = 0;
=======
public:
	ChessPiece(char type);
	virtual ~ChessPiece() = 0;
	virtual bool checkMove(int curRow, int curCol, int newRow, int newCol) = 0;
>>>>>>> 05f70aeda762d7dd6660e02550f255fd4355d38e:Code/chesspiece.h
};



#endif
