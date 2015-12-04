#ifndef CPU_H
#define CPU_H
#include <string>
#include "player.h"

class CPU: public Player {
	const int level; // can be 1 to 4+
	// level 1 is random legal moves
	// level 2 is capturing > checking > random
	// level 3 is saving pieces > capturing > checks > random
	// level 4 is something more elaborate > saving pieces > capturing > checks > random
public:
	CPU(int number, int level, Game* game);
	virtual ~CPU();
	std::string getMove();
	bool isCPU();
};
#endif
