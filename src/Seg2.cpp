#include "Seg2.h"

Seg2::Seg2()
{
	angle = 0.0f;
}
Seg2::Seg2(Point a, Point b)
{
	angle = 0.0f;
	this->a = a;
	this->b = b;
}

Seg2::~Seg2()
{

}


// Checks if seg1 == seg2
bool operator==(Seg2 seg1, Seg2 seg2){
	return (
		(seg1.a == seg2.a && seg1.b == seg2.b)||
		(seg1.a == seg2.b && seg1.b == seg2.a));
}

// Check if seg1 < seg2 
bool operator<(Seg2 seg1, Seg2 seg2){
	return seg1.angle < seg2.angle;
}