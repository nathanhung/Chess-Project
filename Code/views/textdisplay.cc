#include "textdisplay.h"
#include <iostream>
#include <cassert>
using namespace std;

TextDisplay::TextDisplay(int n): View(n){
assert(GRIDSIZE);
theDisplay = new char* [GRIDSIZE];
  for(int i = 0; i < GRIDSIZE; i++){
    theDisplay[i] = new char[GRIDSIZE];
    assert(theDisplay[i]);
    // setup the row indices
    for(int j = 0; j < GRIDSIZE; j++){
        // setup initial chars
        theDisplay[i][j] = ((i+j) % 2)? '-': ' ';
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
    	// eigth row	
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

TextDisplay::~TextDisplay(){
	for(int i = 0; i < GRIDSIZE; i++){
		delete [] theDisplay[i];
	}
	delete theDisplay;
}

void TextDisplay::print(){
    cout << endl;
    assert(theDisplay);
    assert(GRIDSIZE);
	for(int i = 0; i < GRIDSIZE; i++){
        cout << 8 - i << " ";
		for(int j = 0; j < GRIDSIZE; j++){
			cout << theDisplay[i][j];
		}
		cout << endl;
	}
    cout << "  " << "abcdefgh" << endl;
}

void TextDisplay::notify(int row, int col, char newChar){
    assert(theDisplay);
    assert(row > -1 && col > -1);
    theDisplay[row][col] = newChar;
}
