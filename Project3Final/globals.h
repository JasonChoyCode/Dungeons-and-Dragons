#ifndef globals_h
#define globals_h

#include "utilities.h"

const int n_rows = 18;
const int n_cols = 70;

//code to assist with the creation of rooms
class Rooms
{
public:
	Rooms(int r, int c, int w, int h);
	int getRows() const;
	int getCols() const;
	int getWidth() const;
	int getHeight() const;
private:
	int rows;
	int cols;
	int width;
	int height;
};

#endif