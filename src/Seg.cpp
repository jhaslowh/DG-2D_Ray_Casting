#include "Seg.h"


Seg::Seg()
{
    deletePoints = false;
    angle = 0.0f;
    a = NULL;
    b = NULL;
}
Seg::Seg(Point* a, Point* b)
{
    deletePoints = false;
    angle = 0.0f;
    this->a = a;
    this->b = b;
}

Seg::~Seg()
{
    if (deletePoints){
        delete a;
        delete b;
    }
}


// Checks if seg1 == seg2
bool operator==(Seg seg1, Seg seg2){
    return (
        (seg1.a == seg2.a && seg1.b == seg2.b)||
        (seg1.a == seg2.b && seg1.b == seg2.a));
}

// Check if seg1 < seg2 
bool operator<(Seg seg1, Seg seg2){
    return seg1.angle < seg2.angle;
}