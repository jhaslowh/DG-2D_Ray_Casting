#pragma once
#include "glew.h"
#include "GLHandler.h"
#include "Point.h"
#include "UIAtlas.h"

class Box
{
	// Location and size
	float locX,locY,width,height;
	// Corners 
	Point tlC,trC,blC,brC;
	// Box color
	GLfloat color[4];

public:
	// Make a new box with default properties
	Box();
	// Make a new box with sent properties 
	Box(float x, float y, float w, float h);
	~Box();

	// Set location of the box 
	void setLocation(float x, float y);
	// Set x location of box 
	void setX(float x);
	// Get x location of box
	float getX();
	// Set y location of box
	void setY(float y);
	// Get y location of box 
	float getY();
	// Set box size 
	void setSize(float w, float h);
	// Set width of box 
	void setWidth(float w);
	// Get box width 
	float getWidth();
	// Set height of box 
	void setHeight(float h);
	// Get box height 
	float getHeight();
	// Set box color
	void setColor(float r, float g, float b, float a);

	// Get boxs top left corner
	Point* getCornerTopLeft();
	// Get boxs top right corner
	Point* getCornerTopRight();
	// Get boxs bottom left corner
	Point* getCornerBottomLeft();
	// Get boxs bottom right corner 
	Point* getCornerBottomRight();

	// Draw rec
	void draw(GLHandler* mgl, UIAtlas* mUI);

	// Check if box contains sent point
	bool contains(float x, float y);

private:

	// Fix corner locations 
	void fixCorners();
};

