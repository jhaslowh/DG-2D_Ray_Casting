#pragma once
class SortPoint
{
public:
	Seg seg;
	float angle;

	SortPoint();
	~SortPoint();

	// Check which angle is lower 
	friend bool operator<(SortPoint p1, SortPoint p2);
};

