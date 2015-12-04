#include "controller.h"
#include <iostream>
using namespace std;

/*
 * TODO: update main function to take argument "-graphics" for part b. 
 * If -graphics argument is provided, forward this to the controller
 */
int main () {
    Controller c("graphics");

    #ifdef DEBUG
    cout << "Starting game...(main.cc: 11)" << endl;
    #endif
    
    c.playGame();
}
