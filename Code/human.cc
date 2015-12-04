#include "human.h"

Human::Human(int number, Game* game): Player(number, game){}

Human::~Human(){}

bool Human::isCPU(){
	return false;
}

std::string Human::getMove(){
	return "";
}
