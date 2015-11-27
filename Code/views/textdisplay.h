#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"

class TextDisplay: public View{
	char** theDisplay;
public:
	TextDisplay();
	virtual ~TextDisplay();
	void print();
};

#endif
