#include "convert.h"
int colToIndex(char c){
	return  c - 'a';
}
// assumes we have an integer (do - '0')
int rowToIndex(char c){
	return  8 - c;
}

char toRow(int n){
	return 8 - n + '0';
}

char toColumn(int n){
	return  n + 'a';
}
