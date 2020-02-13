#include "BoxHandler.h"


BoxHandler::BoxHandler()
{
    capacity = 50;
    boxes = new Box*[capacity];
    for (int i = 0; i < capacity; i++){
        boxes[i] = NULL;
    }
}

BoxHandler::BoxHandler(int s)
{
    capacity = s;
    boxes = new Box*[capacity];
    for (int i = 0; i < capacity; i++){
        boxes[i] = NULL;
    }
}

BoxHandler::~BoxHandler()
{
    if (boxes == NULL) return;
    for (int i = 0; i < capacity; i++){
        delete boxes[i];
        boxes[i] = NULL;
    }
    delete[] boxes;
    boxes = NULL;
}

// Get total count of elements
int BoxHandler::getSize(){return size;}    
// Get total number that can be stored 
int BoxHandler::getCapacity(){return capacity;}

// Get boxes
Box** BoxHandler::getBoxes(){return boxes;}

// Draw boxes 
void BoxHandler::draw(GLHandler* mgl, UIAtlas* mUI){
    for (int i = 0; i < capacity; i++){
        if (boxes[i] != NULL)
            boxes[i]->draw(mgl, mUI);
    }
}

// Add new box 
Box* BoxHandler::add(float x, float y, float w, float h){
    for (int i = 0; i < capacity; i++){
        if (boxes[i] == NULL){
            Box* b = new Box(x,y,w,h);
            b->setColor(0.0f,0.0f,0.0f,1.0f);
            boxes[i] = b;
            size++;
            return b;
        }
    }
    return NULL;
}

// Remove 
void BoxHandler::remove(Box* box){
    for (int i = 0; i < capacity; i++){
        if (boxes[i] == box){
            boxes[i] = NULL;
            delete box;
            size--;
        }
    }
}

// Clear handlers
void BoxHandler::clear(){
    for (int i = 0; i < capacity; i++){
        delete boxes[i];
        boxes[i] = NULL;
    }
    size = 0;
}

// Find the box that contains the point
Box* BoxHandler::contains(float x, float y){
    for (int i = 0; i < capacity; i++){
        if (boxes[i] != NULL && boxes[i]->contains(x,y)){
            return boxes[i];
        }
    }
    return NULL;
}
