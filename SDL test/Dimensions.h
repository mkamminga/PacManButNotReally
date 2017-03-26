#pragma once
#include "Vector2D.h"

struct Dimension {
	int height = 0;
	int width = 0;
	int x0 = 0;
	int x1 = 0;
	int y0 = 0;
	int y1 = 0;

	Dimension() {}

	Dimension(int height,
	int width,
	int x0,
	int x1,
	int y0,
	int y1) : height(height), width(width), x0(x0), x1(x1), y0(y0), y1(y1) {

	}

	bool withinBounds(int x, int y)
	{
		return (x >= x0 && x <= x1) && (y >= y0 && y <= y1);
	}

	bool withinBounds(Vector2D& vector)
	{
		return (vector.x >= x0 && vector.x <= x1) && (vector.y >= y0 && vector.y <= y1);
	}
};