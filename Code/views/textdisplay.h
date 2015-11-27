#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"

class TextDisplay: public View{
	char** theDisplay;
public:
	TextDisplay(int n);
	virtual ~TextDisplay();
	void print();
	virtual void notify(int row, int col, char newChar);
};

#endif
