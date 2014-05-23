#include "LightMap.h"


LightMap::LightMap()
{
	lightX = lightY = 300.0f;
	lightRaySize = 500.0f;
	valid = false;

	// Drawing properties 
	lightArray = NULL;
	indicies = NULL;
	nlightArray = NULL;
	nindicies = NULL;
	iCount = 0;
}

LightMap::~LightMap(void)
{
	delete[] lightArray;
	lightArray = NULL;
	delete[] indicies;
	indicies = NULL;
	delete[] nlightArray;
	nlightArray = NULL;
	delete[] nindicies;
	nindicies = NULL;
}

// Set the location for the light 
void LightMap::setLightLoc(float x, float y){
	lightX = x;
	lightY = y;
	valid = false;
}

// Set the size of the rays
void LightMap::setLightSize(float value){
	lightRaySize = value;
	valid = false;
}
// Get the size of the rays
float LightMap::getLightSize(){
	return lightRaySize;
}

// Invalidate map
void LightMap::invalidate(){
	valid = false;
}

// Update map state
void LightMap::update(float deltaTime){
	if (!valid){
		makeMap();
	}
}

// Draw map state
void LightMap::drawMap(GLHandler* mgl){
	if (clearDrawb)
		clearDraw();

	if (valid){
		mgl->setFlatColor(.5f,.5f,.5f,1.0f);
		mgl->setModelMatrix(glm::mat4());

		// Swap arrays if new array 
		if (nlightArray != NULL){
			delete[] lightArray;
			delete[] indicies;
			lightArray = nlightArray;
			indicies = nindicies;
			nlightArray = NULL;
			nindicies = NULL;
			iCount = niCount;
		}

		if (iCount != 0){
			/// Set up vertex and coord buffers 
			glEnableVertexAttribArray(mgl->mPositionHandle);
			glVertexAttribPointer(mgl->mPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, lightArray );
		
			glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_SHORT, indicies);
		}
	}
}

// Add points
void LightMap::addPoint(Point* p){
	points.push_back(p);
	valid = false;
}

// Remove point from map
void LightMap::removePoint(Point* p){
	points.remove(p);
	valid = false;
}

// Add segs
void LightMap::addSeg(Seg seg){
	segs.push_back(seg);
	valid = false;
}

// Remove seg from map
void LightMap::removeSeg(Seg seg){
	segs.remove(seg);
}

// Clear map
void LightMap::clear(){
	points.clear();
	segs.clear();
	clearDrawb = true;
}

// Clear draw values 
void LightMap::clearDraw(){
	clearDrawb = false;
	iCount = 0;
	delete[] lightArray;
	lightArray = NULL;
	delete[] indicies;
	indicies = NULL;
	delete[] nlightArray;
	nlightArray = NULL;
	delete[] nindicies;
	nindicies = NULL;
}

// Create new map 
void LightMap::makeMap(){
	std::cout << "Update map\n";

	// Create Rays 
	// TODO 

	// Clip Rays 
	// TODO 

	valid = true;
}