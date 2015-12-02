#ifndef VIEW_H
#define VIEW_H

class View {
protected:
	const int GRIDSIZE;
public:
	//virtual void notify() = 0; // what does this do?
	virtual void print() = 0;
	virtual void notify(int row, int col, char newChar) = 0;
	View(int n);
	virtual ~View();
};

#endif
