#pragma once
#include <list>
#include <math.h>
#include "glew.h"

#include "BoxHandler.h"
#include "Collision.h"
#include "GLHandler.h"
#include "Seg.h"
#include "Seg2.h"
#include "UIAtlas.h"

#define PI_2 6.283185f
#define PI 3.1415926f
#define SECOND_ANGLE_DIFF .01f

class LightMap
{
    // Light properties 
    float lightX, lightY;
    float lightRaySize;
    bool valid;
    int rayCount;

    // Lists
    std::list<Point*> points;
    std::list<Seg> segs;
    std::list<Seg2> rays;
    std::list<Point> rayEnds;

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

    // Bool for which method to use 
    bool useMethod1;

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

    // Set the ray count
    void setRayCount(int count);
    // Get the ray count
    int getRayCount();

    // Set which method to use
    void setMethod1(bool value);

    // Invalidate map
    void invalidate();

    // Update map state
    void update(float deltaTime);

    // Draw map state
    void drawMap(GLHandler* mgl);

    // Draw debug
    void drawDebug(GLHandler* mgl, UIAtlas* mUI);

    // Add segs
    void addSeg(Seg seg);

    // Remove seg from map
    void removeSeg(Seg seg);

    // Add points
    void addPoint(Point* p);

    // Remove point from map
    void removePoint(Point* p);

    // Clear map
    void clear();

private: 

    // Clear draw values 
    void clearDraw();

    // Create new map 
    void makeMap();

    // Create new map wtih method 2
    void makeMap2();
};

