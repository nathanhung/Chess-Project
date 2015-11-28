#ifndef CHESSPIECE_H
#define CHESSPIECE_H


class ChessPiece {
	char owner;
	char type;

	public:
		ChessPiece();
		virtual ~ChessPiece() = 0;
		virtual checkMove(int row1, int col1, int row2, int col2) = 0;
		
}



#endif
