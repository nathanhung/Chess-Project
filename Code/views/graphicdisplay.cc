#include "graphicdisplay.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include "../tile.h"
#include "../pieces/chesspiece.h"
#include "window.h"
using namespace std;

GraphicDisplay::GraphicDisplay(int n): View(n){
assert(GRIDSIZE);
theDisplay = new char* [GRIDSIZE];
// initialize pointer to Xwindow
pXwindow = new Xwindow;

  for(int i = 0; i < GRIDSIZE; i++){
    theDisplay[i] = new char[GRIDSIZE];
    assert(theDisplay[i]);
    // setup the row indices
    for(int j = 0; j < GRIDSIZE; j++){
        // setup initial chars
        theDisplay[i][j] =  ' ';
    	// do first row
    	if(i == 0){
    		if(j == 0 || j == 7){
    			theDisplay[i][j] = 'r';
    		}
    		else if(j == 1 || j == 6){
    			theDisplay[i][j] = 'n';
    		}
    		else if(j == 2 || j == 5){
    			theDisplay[i][j] = 'b';
    		}
    		else if(j == 3){
    			theDisplay[i][j] = 'q';
    		}
    		else{
    			theDisplay[i][j] = 'k';
    		}
    	}
    	// do second row
    	else if(i == 1){
    		theDisplay[i][j] = 'p';
    	}
    	// seventh row
    	else if(i == 6){
    		theDisplay[i][j] = 'P';
    	}
    	// eighth row	
    	else if(i == 7){
    		if(j == 0 || j == 7){
    			theDisplay[i][j] = 'R';
    		}
    		else if(j == 1 || j == 6){
    			theDisplay[i][j] = 'N';
    		}
    		else if(j == 2 || j == 5){
    			theDisplay[i][j] = 'B';
    		}
    		else if(j == 3){
    			theDisplay[i][j] = 'K';
    		}
    		else{
    			theDisplay[i][j] = 'Q';
    		}
    	}
        assert(theDisplay[i][j]);
    }
  }
}

GraphicDisplay::~GraphicDisplay(){
	for(int i = 0; i < GRIDSIZE; i++){
		delete [] theDisplay[i];
	}
	delete theDisplay;
	delete pXwindow; // call Xwindows dtor
}
                 
void GraphicDisplay::print(){

    assert(theDisplay);
    assert(GRIDSIZE);
	for (int i  = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE; j++) {
			pXwindow->fillRectangle(50 * i + 50, 50 * j, 50, 50, ((i + j) % 2)? Xwindow::Yellow : Xwindow::White);
		}
	}

	for(int i = 0; i < GRIDSIZE; i++){
		int n = i;
		n = 8 - n;
		stringstream ss;
		ss << n;
		string s = ss.str();
		pXwindow->drawString(25, 50 * i + 25, s, Xwindow::Black);	  	

		for(int j = 0; j < GRIDSIZE; j++){
			stringstream ss2;
			ss2 << theDisplay[i][j];
			string s2 = ss2.str();
			if (s2 == "-") {
				s2 = "";
			}
			pXwindow->drawBigString(50 * (j + 1) + 25, 50 * i + 25, s2, Xwindow::Black);			
		}
	}
	pXwindow->drawString(50 * 1 + 25, 425, "a", Xwindow::Black);
	pXwindow->drawString(50 * 2 + 25, 425, "b", Xwindow::Black);
	pXwindow->drawString(50 * 3 + 25, 425, "c", Xwindow::Black);
	pXwindow->drawString(50 * 4 + 25, 425, "d", Xwindow::Black);
	pXwindow->drawString(50 * 5 + 25, 425, "e", Xwindow::Black);
	pXwindow->drawString(50 * 6 + 25, 425, "f", Xwindow::Black);
	pXwindow->drawString(50 * 7 + 25, 425, "g", Xwindow::Black);
	pXwindow->drawString(50 * 8 + 25, 425, "h", Xwindow::Black); 
}

void GraphicDisplay::notify(int row, int col, char newChar){
    assert(theDisplay);
    assert(row > -1 && col > -1);
    theDisplay[row][col] = newChar;
}

void GraphicDisplay::update(Tile** theGrid){

    for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            if(theGrid[i][j].getPiece()){
                theDisplay[i][j] = theGrid[i][j].getPiece()->getType();
            }
            else{
                theDisplay[i][j] = ((i+j) % 2)? '-': ' ';
            }
        }
    }
}
