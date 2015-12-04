#include "controller.h"
#include <iostream>
using namespace std;

/*
 * TODO: update main function to take argument "-graphics" for part b. 
 * If -graphics argument is provided, forward this to the controller
 */
int main(int argc, char* argv[]) {
	Controller c;

	if(argc > 1){
		c.readFile(argv[1]);
	}
	
    #ifdef DEBUG
    cout << "Starting game...(main.cc: 11)" << endl;
    #endif
    
    c.playGame();
}
