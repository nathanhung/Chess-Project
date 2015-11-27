#ifndef VIEW_H
#define VIEW_H

class View {

	const int GRIDSIZE;
	virtual void notify() = 0;
	virtual void print() = 0;
	virtual void notify(int row, int col, char newChar) = 0;

	View();
	virtual ~View() = 0;
};

#endif
