
class Player;

class ChessPiece {
	Player* owner;
	char type;

	ChessPiece(char type);
	virtual ~ChessPiece() = 0;
};
