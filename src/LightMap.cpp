#include "LightMap.h"


LightMap::LightMap()
{
	lightX = lightY = 300.0f;
	lightRaySize = 500.0f;
	valid = false;
	clearDrawb = false;
	rayCount = 180;
	useMethod1 = true;

	// Drawing properties 
	lightArray = NULL;
	indicies = NULL;
	nlightArray = NULL;
	nindicies = NULL;
	iCount = 0;
	niCount = 0;

	bHand = NULL;
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

// Set the ray count
void LightMap::setRayCount(int count){
	rayCount = count;
	valid = false;
}
// Get the ray count
int LightMap::getRayCount(){return rayCount;}

// Set which method to use
void LightMap::setMethod1(bool value){useMethod1 = value;}

// Invalidate map
void LightMap::invalidate(){
	valid = false;
}

// Update map state
void LightMap::update(float deltaTime){
	if (!valid){
		if (useMethod1)
			makeMap();
		else
			makeMap2();
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

// Draw debug
void LightMap::drawDebug(GLHandler* mgl, UIAtlas* mUI){
	mgl->setFlatColor(1.0f, 0.0f, 0.0f, 1.0f);

	for (std::list<Point>::iterator it = rayEnds.begin(); it != rayEnds.end(); it++){
		mUI->drawScale2(mgl, UII_REC, (*it).getX() - 1.0f, (*it).getY(), 2.0f, 2.0f);
	}
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
	// Clear array list 
	rays.clear();
	rayEnds.clear();

	// Check if inside any boxes 
	if (bHand != NULL && bHand->contains(lightX, lightY)){
		std::cout << "ERROR: Light point in wall\n";
	}
	else {
		// -----------------------
		// Create Rays 
		Seg2 seg;		// Segment for use during algorithm
		Point inter;	// Intersection point 
		float current = -PI;	// Current angle for ray to add
		float angle = 0.0f;		// Angle used when adding rays for wall segments 
		float spacing = PI_2 / (float)rayCount; // Angular spacing between rays 
		std::list<Seg> walls;
		Seg* wall = NULL;

		// Add rays at interval 
		for (int i = 0; i < rayCount; i++){
			// Make ray 
			seg.a.setLocation(lightX, lightY);
			seg.b.setLocation(
				lightX + (cos(current) * lightRaySize),
				lightY + (sin(current) * lightRaySize));
			seg.angle = current;

			// Clip Ray by checking intersection with walls 
			for (std::list<Seg>::iterator it2 = segs.begin(); it2 != segs.end(); it2++){
				// Check if ray intercepts wall 
				if (checkSegSeg((seg.a), (seg.b), *((*it2).a), *((*it2).b), &inter)){
					// Shrink Ray 
					seg.b.setLocation(inter.getX(), inter.getY());

					// Set current wall as closest wall
					wall = &(*it2);
				}
			}

			// Add closest wall to wall list 
			if (wall != NULL){
				bool wallfound = false;
				for (std::list<Seg>::iterator it = walls.begin(); it != walls.end(); it++){
					if (*wall == *it)
						wallfound = true;
				}

				if (!wallfound)
					walls.push_back(*wall);
				wall = NULL;
			}
		
			// Add ray to list 
			rays.push_back(seg);

			// Move up angle 
			current += spacing;
		}

		// For each wall connected to light source, add ray for end points. 
		for (std::list<Seg>::iterator it = walls.begin(); it != walls.end(); it++){
			// Check distance 
			if (dist(lightX, lightY, (*it).a->getX(), (*it).a->getY()) < lightRaySize){
				// Add point a 
				angle = atan2((*it).a->getY() - lightY, (*it).a->getX() - lightX);
				// Make ray 
				seg.a.setLocation(lightX, lightY);
				seg.b.setLocation((*it).a->getX(),(*it).a->getY());
				seg.angle = angle;

				// Clip Ray by checking intersection with walls 
				for (std::list<Seg>::iterator it2 = segs.begin(); it2 != segs.end(); it2++){
					// Check if ray intercepts wall 
					if (checkSegSeg((seg.a), (seg.b), *((*it2).a), *((*it2).b), &inter)){
						// Shrink Ray 
						seg.b.setLocation(inter.getX(), inter.getY());
					}
				}

				// Add ray to list 
				rays.push_back(seg);
			}

			// Check distance 
			if (dist(lightX, lightY, (*it).b->getX(), (*it).b->getY()) < lightRaySize){
				// Add point b 
				angle = atan2((*it).b->getY() - lightY, (*it).b->getX() - lightX);
				// Make ray 
				seg.a.setLocation(lightX, lightY);
				seg.b.setLocation((*it).b->getX(),(*it).b->getY());
				seg.angle = angle;

				
				// Clip Ray by checking intersection with walls 
				for (std::list<Seg>::iterator it2 = segs.begin(); it2 != segs.end(); it2++){
					// Check if ray intercepts wall 
					if (checkSegSeg((seg.a), (seg.b), *((*it2).a), *((*it2).b), &inter)){
						// Shrink Ray 
						seg.b.setLocation(inter.getX(), inter.getY());
					}
				}

				// Add ray to list 
				rays.push_back(seg);
			}
		}

		// Sort arrays by angles
		rays.sort();
	}
	
	// -----------------------
	// Make drawing triangles 
	int count = (rays.size() + 1) * 2;      // Number of vertexes 
	niCount = rays.size() * 3;	            // Number of indicies 

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
	for (std::list<Seg2>::iterator it = rays.begin(); it != rays.end(); it++){
		rayEnds.push_back(Point((*it).b.getX(), (*it).b.getY()));
		nlightArray[index] = (*it).b.getX();
		index++;
		nlightArray[index] = (*it).b.getY();
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

	valid = true;
}

// Create new map wtih method 2
void LightMap::makeMap2(){
	// Clear array list 
	rays.clear();
	rayEnds.clear();

	// Check if inside any boxes 
	if (bHand != NULL && bHand->contains(lightX, lightY)){
		std::cout << "ERROR: Light point in wall\n";
	}
	else{
		// -----------------------
		// Create Rays 
		float angle;
		Seg2 seg;
		// points here are the corners of the drawn boxes and the corners of the screen. 
		for (std::list<Point*>::iterator it = points.begin(); it != points.end(); it++){
			// Get angle of ray. From light source to the point.  
			angle = atan2((*it)->getY() - lightY, (*it)->getX() - lightX);
			// Make ray. From the light source to the point end. Length is given light size. 
			seg.a.setLocation(lightX, lightY);
			seg.b.setLocation(
				lightX + (cos(angle) * lightRaySize),
				lightY + (sin(angle) * lightRaySize));
			// Check if point is closer than ray end. If it is then set it as the
			// endpoint of the segment instead of light ray current end. 
			if (dist(lightX, lightY, (*it)->getX(), (*it)->getY()) < 
				dist(lightX, lightY, seg.b.getX(), seg.b.getY()))
				seg.b.setLocation((*it)->getX(), (*it)->getY());
			// Set angle for segment 
			seg.angle = angle;
			// Add ray to list 
			rays.push_back(seg);

			// Add second line that is a slight offset from the original ray based on the
			// center location of the box the ray was build from. This can be observed when 
			// watching the rays interact with corners. 
			// - Adding the second line fixes errors with the corners not appearing correctly. 
			// - And also fixes a flickering issue. 
			if ((*it)->box != NULL){
				// Get box of ray 
				angle = atan2(
					((Box*)((*it)->box))->getCenterY() - lightY, 
					((Box*)((*it)->box))->getCenterX() - lightX);

				// Get angular direction (-1 | 1) 
				float direc = seg.angle - angle;
				direc /= abs(direc);

				// Make second ray
				// Get angle of ray
				angle = seg.angle + (SECOND_ANGLE_DIFF * direc);
				// Make ray
				seg.a.setLocation(lightX, lightY);
				seg.b.setLocation(
					lightX + (cos(angle) * lightRaySize),
					lightY + (sin(angle) * lightRaySize));
				seg.angle = angle;
				// Add ray to list 
				rays.push_back(seg);
			}
		}
	
		// -----------------------
		// Clip Rays. This checks if any rays intercept the walls and then 
		// clips them by the intersection point. 
		Point inter;
		for (std::list<Seg2>::iterator it = rays.begin(); it != rays.end(); it++){
			for (std::list<Seg>::iterator it2 = segs.begin(); it2 != segs.end(); it2++){
				// Check if ray intercepts wall 
				if (checkSegSeg(((*it).a), ((*it).b), *((*it2).a), *((*it2).b), &inter)){
					// Add interception as new end point 
					(*it).b.setLocation(inter.getX(), inter.getY());
				}
			}
		}

		// -----------------------
		// Sort arrays by angles.
		rays.sort();
	}

	// -----------------------
	// Make drawing triangles 
	int count = (rays.size() + 1) * 2;     // Number of vertexes 
	niCount = rays.size() * 3;	           // Number of indicies 

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
	for (std::list<Seg2>::iterator it = rays.begin(); it != rays.end(); it++){
		rayEnds.push_back(Point((*it).b.getX(), (*it).b.getY()));
		nlightArray[index] = (*it).b.getX();
		index++;
		nlightArray[index] = (*it).b.getY();
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
	

	valid = true;
}