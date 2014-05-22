#pragma once
#include "Box.h"

class BoxHandler
{
	int size, capacity;
	Box** boxes;

public:
	BoxHandler();
	BoxHandler(int size);
	~BoxHandler();

	// Get size of handler
	int getSize();

	// Get boxes
	Box** getBoxes();

	// Draw boxes 
	void draw(GLHandler* mgl, UIAtlas* mUI);

	// Add new box 
	Box* add(float x, float y, float w, float h);

	// Remove 
	void remove(Box* box);

	// Find the box that contains the point
	Box* contains(float x, float y);
};

