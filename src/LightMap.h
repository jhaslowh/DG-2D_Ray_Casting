#pragma once
#include <list>
#include <math.h>
#include "glew.h"

#include "BoxHandler.h"
#include "Collision.h"
#include "GLHandler.h"
#include "Seg.h"

#define PI_2 6.283185f

class LightMap
{
	// Light properties 
	float lightX, lightY;
	float lightRaySize;
	bool valid;
	int rayCount;

	// Lists
	std::list<Seg> segs;
	std::list<Seg> rays;

	// Drawing properties 
	int iCount;
	GLfloat* lightArray;
	GLshort* indicies;
	// New arrays to be swapped 
	int niCount;
	GLfloat* nlightArray;
	GLshort* nindicies;

	// Set to true to clear drawing values 
	bool clearDrawb;

public:
	BoxHandler* bHand;

	LightMap();
	~LightMap();

	// Set the location for the light 
	void setLightLoc(float x, float y);

	// Set the size of the rays
	void setLightSize(float value);
	// Get the size of the rays
	float getLightSize();

	// Invalidate map
	void invalidate();

	// Update map state
	void update(float deltaTime);

	// Draw map state
	void drawMap(GLHandler* mgl);

	// Add segs
	void addSeg(Seg seg);

	// Remove seg from map
	void removeSeg(Seg seg);

	// Clear map
	void clear();

private: 

	// Clear draw values 
	void clearDraw();

	// Create new map 
	void makeMap();
};

