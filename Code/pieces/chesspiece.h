#ifndef CHESSPIECE_H
#define CHESSPIECE_H
class Game;

class ChessPiece {
	char owner;
	char type;
	Game* game;
	public:
		ChessPiece(char owner, char type, Game* game); //ctor
		virtual ~ChessPiece() = 0;
		virtual bool checkMove(int curRow, int curCol, int newRow, int newCol) = 0;
};



#endif
