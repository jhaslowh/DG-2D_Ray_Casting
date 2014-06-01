#pragma once
#include "Point.h"
class Seg2
{
public:
	float angle;
	Point a;
	Point b;

	Seg2();
	Seg2(Point a, Point b);
	~Seg2();

	// Checks if seg1 == seg2
 	friend bool  operator==(Seg2 seg1, Seg2 seg2);
	
	// Check if seg1 < seg2 
 	friend bool  operator<(Seg2 seg1, Seg2 seg2);
};

