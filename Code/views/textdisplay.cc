#include "textdisplay.h"
#include <iostream>
using namespace std;

TextDisplay::TextDisplay(int n): View(n){

char** arr = new char* [GRIDSIZE];
  for(int i = 0; i < GRIDSIZE; ++i){
    arr[i] = new char[GRIDSIZE];
    // setup the row indices
    for(int j = 0; j < GRIDSIZE; j++){
    	// do first row
    	if(i == 0){
    		if(j == 0 || j == 7){
    			arr[i][j] = 'r';
    		}
    		else if(j == 1 || j == 6){
    			arr[i][j] = 'n';
    		}
    		else if(j == 2 || j == 5){
    			arr[i][j] = 'b';
    		}
    		else if(j == 3){
    			arr[i][j] = 'q';
    		}
    		else{
    			arr[i][j] = 'k';
    		}
    	}
    	// do second row
    	else if(i == 1){
    		arr[i][j] = 'p';
    	}
    	// seventh row
    	else if(i == 6){
    		arr[i][j] = 'P';
    	}
    	// eigth row	
    	else if(i == 7){
    		if(j == 0 || j == 7){
    			arr[i][j] = 'R';
    		}
    		else if(j == 1 || j == 6){
    			arr[i][j] = 'N';
    		}
    		else if(j == 2 || j == 5){
    			arr[i][j] = 'B';
    		}
    		else if(j == 3){
    			arr[i][j] = 'K';
    		}
    		else{
    			arr[i][j] = 'Q';
    		}
    	}
    	else{
    		arr[i][j] = ((i+j) % 2)? '-': ' ';
    	}
    }
  }
  theDisplay = arr;
}

TextDisplay::~TextDisplay(){
	for(int i = 0; i < GRIDSIZE; i++){
		delete [] theDisplay[i];
	}

	delete theDisplay;
}

void TextDisplay::print(){
	for(int i = 0; i < GRIDSIZE; i++){
        cout << 8 - i << " ";
		for(int j = GRIDSIZE; j < GRIDSIZE; j++){
			cout << theDisplay[i][j];
		}
		cout << endl;
	}
    cout << "  " << "abcdefgh" << endl;
}

void TextDisplay::notify(int row, int col, char newChar){
    theDisplay[row][col] = newChar;
}