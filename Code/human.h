#ifndef HUMAN_H
#define HUMAN_H

class Human: public Player{
public:
	Human(Tile** theGrid);
	virtual ~Human();
	//virtual string getMove();  Is this needed?
};

#endif
