#ifndef CPU_H
#define CPU_H

class CPU: public Player {
	int level; // can be 1 to 4+
	// level 1 is random legal moves
	// level 2 is capturing > checking > random
	// level 3 is saving pieces > capturing > checks > random
	// level 4 is something more elaborate > saving pieces > capturing > checks > random
public:
	CPU();
	virtual ~CPU();
	virtual string getMove();
};
#endif
