#include "Box.h"

// Make a new box with default properties
Box::Box(){
    locX = locY = width = height = 0.0f;
    centerX = centerY = 0.0f;
    color[0] = color[1] = color[2] = color[3] = 1.0f;
    fixCorners();
}
// Make a new box with sent properties 
Box::Box(float x, float y, float w, float h){
    locX = x;
    locY = y;
    width = w;
    height = h;
    centerX = x + (width * .5f);
    centerY = y + (height * .5f);
    color[0] = color[1] = color[2] = color[3] = 1.0f;
    fixCorners();
}
Box::~Box(){};
    
// Set location of the box 
void Box::setLocation(float x, float y){
    locX = x;
    locY = y;
    fixCorners();
}
// Set x location of box 
void Box::setX(float x){
    locX = x;
    fixCorners();
}
// Get x location of box
float Box::getX(){return locX;}
// Set y location of box
void Box::setY(float y){
    locY = y;
    fixCorners();
}
// Get y location of box 
float Box::getY(){return locY;}
// Set box size 
void Box::setSize(float w, float h){
    width = w;
    height = h;
    fixCorners();
}
// Set width of box 
void Box::setWidth(float w){
    width = w;
    fixCorners();
}
// Get box width 
float Box::getWidth(){return width;}
// Set height of box 
void Box::setHeight(float h){
    height = h;
    fixCorners();
}
// Get box height 
float Box::getHeight(){return height;}
// Set box color
void Box::setColor(float r, float g, float b, float a){
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}
float Box::getCenterX(){return centerX;}
float Box::getCenterY(){return centerY;}

// Get boxs top left corner
Point* Box::getCornerTopLeft(){return &tlC;}
// Get boxs top right corner
Point* Box::getCornerTopRight(){return &trC;}
// Get boxs bottom left corner
Point* Box::getCornerBottomLeft(){return &blC;}
// Get boxs bottom right corner 
Point* Box::getCornerBottomRight(){return &brC;}

// Draw rec
void Box::draw(GLHandler* mgl, UIAtlas* mUI){
    mgl->setFlatColor(color);
    mUI->drawScale2(mgl, UII_REC, locX, locY, width, height);
}


// Check if box contains sent point
bool Box::contains(float x, float y){
    if (x > locX && x < locX + width && y > locY && y < locY + height)
        return true;
    return false;
}

// Fix corner locations 
void Box::fixCorners(){
    tlC.setLocation(locX,locY);
    tlC.box = this;
    trC.setLocation(locX + width, locY);
    trC.box = this;
    blC.setLocation(locX, locY + height);
    blC.box = this;
    brC.setLocation(locX + width, locY + height);
    brC.box = this;
    centerX = locX + (width * .5f);
    centerY = locY + (height * .5f);
}