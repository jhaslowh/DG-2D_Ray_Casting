#pragma once
#include "Point.h"

class Seg
{
public:
	bool deletePoints;
	Point* a;
	Point* b;

	Seg();
	Seg(Point* a, Point* b);
	~Seg();

	// Checks if seg1 == seg2
 	friend bool  operator==(Seg seg1, Seg seg2);
};

