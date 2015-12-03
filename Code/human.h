#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human: public Player{
public:
	Human(int number, Game* game);
	virtual ~Human();
};

#endif
