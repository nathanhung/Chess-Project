#ifndef CONVERT_H
#define CONVERT_H
#include <cassert>

int colToIndex(char c);
// assumes we have an integer (do - '0')
int rowToIndex(char c);

char toRow(int n);

char toColumn(int n);
#endif
