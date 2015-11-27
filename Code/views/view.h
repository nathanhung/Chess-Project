#ifndef VIEW_H
#define VIEW_H

class View {
	const int GRIDSIZE;
	virtual void notify() = 0; // what does this do?
	virtual void print() = 0;
	virtual void notify(int row, int col, char newChar) = 0;
public:
	View(int n);
	virtual ~View() = 0;
};

#endif
