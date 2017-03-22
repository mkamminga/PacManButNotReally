#pragma once

struct Dimension {
	int height = 0;
	int width = 0;
	int x0 = 0;
	int x1 = 0;
	int y0 = 0;
	int y1 = 0;

	bool withinBounds(int x, int y)
	{
		return (x >= x0 && x <= x1) && (y >= y0 && y <= y1);
	}
};