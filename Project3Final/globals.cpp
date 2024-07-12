#include "globals.h"

Rooms::Rooms(int r, int c, int w, int h)
	: rows(r), cols(c), width(w), height(h)
{}


//accessors
int Rooms::getRows() const
{
	return rows;
}
int Rooms::getCols() const
{
	return cols;
}
int Rooms::getWidth() const
{
	return width;
}
int Rooms::getHeight() const
{
	return height;
}