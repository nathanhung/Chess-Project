#ifndef HUMAN_H
#define HUMAN_H

class Human: public Player{
public:
	Human();
	virtual ~Human() = 0;
	virtual string getMove();
};

#endif
