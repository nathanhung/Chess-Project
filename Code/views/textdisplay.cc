#include "textdisplay.h"
#include <iostream>
using namespace std;

TextDisplay::TextDisplay(int n): View(n){

char** arr = new char* [9];
  for(int i = 0; i < 9; ++i){
    arr[i] = new char[9];
    // setup the row indices
    arr[i][0] = 8 - i + '0'; 
    for(int j = 0; j < 9; j++){
    	// do first row
    	if(i == 0){
    		if(j == 1 || j == 8){
    			arr[i][j] = 'r';
    		}
    		else if(j == 2 || j == 7){
    			arr[i][j] = 'n';
    		}
    		else if(j == 3 || j == 6){
    			arr[i][j] = 'b';
    		}
    		else if(j == 4){
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
    		if(j == 1 || j == 8){
    			arr[i][j] = 'R';
    		}
    		else if(j == 2 || j == 7){
    			arr[i][j] = 'N';
    		}
    		else if(j == 3 || j == 6){
    			arr[i][j] = 'B';
    		}
    		else if(j == 4){
    			arr[i][j] = 'K';
    		}
    		else{
    			arr[i][j] = 'Q';
    		}
    	}

    	else if(i == 8){
    		arr[i][j] = j - 1 + 'a';
    	}

    	else{
    		arr[i][j] = ((i+j) % 2)? '-': ' ';
    	}
    }
  }
  arr[8][0] = ' ';
  theDisplay = arr;
}

TextDisplay::~TextDisplay(){
	for(int i = 0; i < 9; i++){
		delete [] theDisplay[i];
	}

	delete theDisplay;
}

void TextDisplay::print(){
	for(int i = 0; i < 9; i++){
		for(int j = 9; j < 9; j++){
			cout << theDisplay[i][j];
		}
		cout << endl;
	}
}

void TextDisplay::notify(int row, int col, char newChar){
    theDisplay[row][col] = newChar;
}
