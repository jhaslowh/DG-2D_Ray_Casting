#include "BoxHandler.h"


BoxHandler::BoxHandler()
{
	size = 50;
	boxes = new Box*[size];
	for (int i = 0; i < size; i++){
		boxes[i] = NULL;
	}
}

BoxHandler::BoxHandler(int s)
{
	size = s;
	boxes = new Box*[size];
	for (int i = 0; i < size; i++){
		boxes[i] = NULL;
	}
}

BoxHandler::~BoxHandler()
{
	if (boxes == NULL) return;
	for (int i = 0; i < size; i++){
		delete boxes[i];
		boxes[i] = NULL;
	}
	delete[] boxes;
	boxes = NULL;
}

// Get size of handler
int BoxHandler::getSize(){return size;}

// Get boxes
Box** BoxHandler::getBoxes(){return boxes;}

// Draw boxes 
void BoxHandler::draw(GLHandler* mgl, UIAtlas* mUI){
	for (int i = 0; i < size; i++){
		if (boxes[i] != NULL)
			boxes[i]->draw(mgl, mUI);
	}
}

// Add new box 
Box* BoxHandler::add(float x, float y, float w, float h){
	for (int i = 0; i < size; i++){
		if (boxes[i] == NULL){
			Box* b = new Box(x,y,w,h);
			b->setColor(0.0f,0.0f,0.0f,1.0f);
			boxes[i] = b;
			return b;
		}
	}
	return NULL;
}

// Remove 
void BoxHandler::remove(Box* box){
	for (int i = 0; i < size; i++){
		if (boxes[i] == box){
			boxes[i] = NULL;
			delete box;
		}
	}
}

// Find the box that contains the point
Box* BoxHandler::contains(float x, float y){
	for (int i = 0; i < size; i++){
		if (boxes[i] != NULL && boxes[i]->contains(x,y)){
			return boxes[i];
		}
	}
	return NULL;
}
