#include "LightMap.h"


LightMap::LightMap()
{
	lightX = lightY = 300.0f;
	lightRaySize = 500.0f;
	valid = false;
	clearDrawb = false;

	// Drawing properties 
	lightArray = NULL;
	indicies = NULL;
	nlightArray = NULL;
	nindicies = NULL;
	iCount = 0;
	niCount = 0;
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
			mgl->toggleTextures(false);
			/// Set up vertex and coord buffers 
			glDisableVertexAttribArray(mgl->mTextCordHandle);
			glEnableVertexAttribArray(mgl->mPositionHandle);
			glVertexAttribPointer(mgl->mPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, lightArray );
		
			glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_SHORT, indicies);
			mgl->toggleTextures(true);
			glDisableVertexAttribArray(mgl->mPositionHandle);
		}
	}
}

// Add points
void LightMap::addPoint(Point* p){
	if (p == NULL){
		std::cout << "ERROR: tried to add null point \n";
	}
	points.push_back(p);
	valid = false;
}

// Remove point from map
void LightMap::removePoint(Point* p){
	if (p == NULL){
		std::cout << "ERROR: tried to remove null point \n";
	}
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
	std::cout << "---------------------\nUpdate map\n---------------------\n";
	// Clear array list 
	rays.clear();

	// TODO check if inside any boxes 

	// -----------------------
	// Create Rays 
	float angle;
	Seg seg;
	for (std::list<Point*>::iterator it = points.begin(); it != points.end(); it++){
		// Get angle of ray 
		angle = atan2((*it)->getY() - lightY, (*it)->getX() - lightX);
		
		// Make ray 
		seg.a = new Point(lightX, lightY);
		seg.b = new Point(
			lightX + (cos(angle) * lightRaySize),
			lightY + (sin(angle) * lightRaySize));
		seg.deletePoints = true;
		seg.angle = angle;

		// Add ray to list 
		rays.push_back(seg);
		seg.a = NULL;
		seg.b = NULL;
	}
	
	// -----------------------
	// Clip Rays 
	Point inter;
	for (std::list<Seg>::iterator it = rays.begin(); it != rays.end(); it++){
		for (std::list<Seg>::iterator it2 = segs.begin(); it2 != segs.end(); it2++){
			// Check if ray intercepts wall 
			if (checkSegSeg(*((*it).a), *((*it).b), *((*it2).a), *((*it2).b), &inter)){
				// Delete old point
				delete (*it).b;
				// Add interception as new end point 
				(*it).b = new Point(inter.getX(), inter.getY());
			}
		}
	}
	
	// -----------------------
	// Sort arrays by angles
	for (std::list<Seg>::iterator it = rays.begin(); it != rays.end(); it++)
		(*it).deletePoints = false;
	rays.sort();
	for (std::list<Seg>::iterator it = rays.begin(); it != rays.end(); it++)
		(*it).deletePoints = true;
	
	// -----------------------
	// Make drawing triangles 
	int count = (rays.size() + 1) * 2;		// Number of vertexes 
	niCount = rays.size() * 3;	// Number of indicies 

	// delete current triagles
	delete[] nlightArray;
	nlightArray = NULL;
	delete[] nindicies;
	nindicies = NULL;

	// Make vertex list 
	nlightArray = new GLfloat[count];
	nlightArray[0] = lightX;
	nlightArray[1] = lightY;
	int index = 2;
	for (std::list<Seg>::iterator it = rays.begin(); it != rays.end(); it++){
		nlightArray[index] = (*it).b->getX();
		index++;
		nlightArray[index] = (*it).b->getY();
		index++;
	}

	// Make index list 
	nindicies = new GLshort[niCount];
	int i2 = 1;
	for (int i = 0; i < niCount; i+=3){
		if (i == 0){
			nindicies[i] = 0;
			nindicies[i+1] = 1;
			nindicies[i+2] = rays.size();
		}
		else {
			nindicies[i] = 0;
			nindicies[i+1] = i2+1;
			nindicies[i+2] = i2;
			i2++;
		}
	}
	/*for (int i = 0; i < niCount; i+=3){
		std::cout << "(" << nindicies[i] << ", " << nindicies[i+1] << ", " << nindicies[i+2] << ")\n";
	}*/

	valid = true;
}