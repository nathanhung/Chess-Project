#ifndef CHESSPIECE_H
#define CHESSPIECE_H


class ChessPiece {
	char owner;
	char type;

	public:
		ChessPiece(char owner, char type); //ctor
		virtual ~ChessPiece() = 0;
		virtual bool checkMove(int curRow, int curCol, int newRow, int newCol) = 0;
		
}



#endif
