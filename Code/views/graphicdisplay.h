#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "view.h"
#include "window.h"

class Tile;
class GraphicDisplay: public View {
        char** theDisplay;
	Xwindow* pXwindow;
public:
        GraphicDisplay(int n);
        virtual ~GraphicDisplay();
        void print();
        virtual void notify(int row, int col, char newChar);
        void update(Tile** theGrid);
};

#endif
