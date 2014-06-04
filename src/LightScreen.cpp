#include "LightScreen.h"


LightScreen::LightScreen() : UIScreen()
{
	// Screen values
	screen_width = screen_height = 0.0f;

	// Menu Values
	menuWidth = 135.0f;

	// States 
	screenShown = true;
	drawLight = false;
	state = LSTATE_MOVE;
	subState = SMOVE_START;

	// Create box handler
	bHand = new BoxHandler(100);
	lightDarkness = .8f;

	// Move state variables 
	moveBox = NULL;

	// Add state variables 
	x1 = x2 = y1 = y2 = 0.0f;

	// UI Components 
	bShow = NULL;
	bHide = NULL;
	bMove = NULL;
	bSetLight = NULL;
	bAdd = NULL;
	bRemove = NULL;
	lTitle = NULL;
	bClear = NULL;
	cbShowLight = NULL;
	lLightSize = NULL;
	vsLightSize = NULL;
	lRayCount = NULL;
	vsRayCount = NULL;
	lDarkness = NULL;
	vsDarkness = NULL;
	cbMethod1 = NULL;
	cbMethod2 = NULL;
}

LightScreen::~LightScreen()
{
	delete bShow;
	bShow = NULL;
	delete bHide;
	bHide = NULL;
	delete bMove;
	bMove = NULL;
	delete bSetLight;
	bSetLight = NULL;
	delete bAdd;
	bAdd = NULL;
	delete bRemove;
	bRemove = NULL;
	delete bHand;
	bHand = NULL;
	delete lTitle;
	lTitle = NULL;
	delete bClear;
	bClear = NULL;
	delete cbShowLight;
	cbShowLight = NULL;
	delete lLightSize;
	lLightSize = NULL;
	delete vsLightSize;
	vsLightSize = NULL;
	delete lRayCount;
	lRayCount = NULL;
	delete vsRayCount;
	vsRayCount = NULL;
	delete lDarkness;
	lDarkness = NULL;
	delete vsDarkness;
	vsDarkness = NULL;
	delete cbMethod1;
	cbMethod1 = NULL;
	delete cbMethod2;
	cbMethod2 = NULL;
}
	
// Initialize screen
void LightScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	this->screen_width = screen_width;
	this->screen_height = screen_height;

	// Create title 
	lTitle = new UILabel(getStateString());
	lTitle->setLocation(menuWidth + 10.0f, 10.0f);
	lTitle->setTextSize(25.0f);
	lTitle->setColor(.058f,.828f,.941f,1.0f);
	lTitle->setupHide(HT_VERTICAL,lTitle->getY()-40.0f,.2f,true);
	lTitle->setHidden();
	// Create screen show button 
	bShow = new UIButton(10.0f,screen_height-45.0f,100.0f,35.0f, std::string("Show"));
	bShow->setupHide(HT_VERTICAL,bShow->getY()+40.0f,.2f,true);
	bShow->setHidden();
	// Create screen hide button 
	bHide = new UIButton(10.0f,screen_height-45.0f,100.0f,35.0f, std::string("Hide"));
	bHide->setupHide(HT_VERTICAL,bHide->getY()-40.0f,.2f,true);
	bHide->setHidden();
	// Create Move button 
	bMove = new UIButton(10.0f,10.0f,100.0f,35.0f, std::string("Move"));
	bMove->setupHide(HT_HOROZONTAL,bMove->getX()-150.0f,.2f,true);
	bMove->setHidden();
	// Create move light button 
	bSetLight = new UIButton(10.0f,50.0f,100.0f,35.0f, std::string("Set Light"));
	bSetLight->setupHide(HT_HOROZONTAL,bSetLight->getX()-150.0f,.2f,true);
	bSetLight->setHidden();
	// Create add button 
	bAdd = new UIButton(10.0f,90.0f,100.0f,35.0f, std::string("Add"));
	bAdd->setupHide(HT_HOROZONTAL,bAdd->getX()-150.0f,.2f,true);
	bAdd->setHidden();
	// Create remove button 
	bRemove = new UIButton(10.0f,130.0f,100.0f,35.0f, std::string("Remove"));
	bRemove->setupHide(HT_HOROZONTAL,bRemove->getX()-150.0f,.2f,true);
	bRemove->setHidden();
	// Create clear button 
	bClear = new UIButton(10.0f,170.0f,100.0f,35.0f, std::string("Clear"));
	bClear->setupHide(HT_HOROZONTAL,bClear->getX()-150.0f,.2f,true);
	bClear->setHidden();
	// Create show light checkbox 
	cbShowLight = new UICheckbox(10.0f, 210.0f,24.0f,24.0f,std::string("Show Light"));
	cbShowLight->setupHide(HT_HOROZONTAL,cbShowLight->getX()-150.0f,.2f,true);
	cbShowLight->setHidden();
	cbShowLight->setTextColor(.8f,.8f,.8f);
	// Create light size label
	lLightSize = new UILabel(std::string("Light Size"));
	lLightSize->setLocation(14.0f, 240.0f);
	lLightSize->setTextSize(16.0f);
	lLightSize->setColor(.8f,.8f,.8f,1.0f);
	lLightSize->setupHide(HT_HOROZONTAL,lLightSize->getX()-150.0f,.2f,true);
	// Create light size value slider
	vsLightSize = new UIValueSlider();
	vsLightSize->setLocation(10.0f, 260.0f);
	vsLightSize->setMinValue(0.0f);
	vsLightSize->setMaxValue(2000.0f);
	vsLightSize->setValue(500.0f);
	vsLightSize->setupHide(HT_HOROZONTAL, vsLightSize->getX() - 150.0f, .2f, true);
	// Create darkness label 
	lDarkness = new UILabel(std::string("Darkness"));
	lDarkness->setLocation(vsLightSize->getX() + 4.0f, vsLightSize->getY() + 30.0f);
	lDarkness->setTextSize(16.0f);
	lDarkness->setColor(.8f,.8f,.8f,1.0f);
	lDarkness->setupHide(HT_HOROZONTAL,lDarkness->getX()-150.0f,.2f,true);
	// Create darkness value slider 
	vsDarkness = new UIValueSlider();
	vsDarkness->setLocation(lDarkness->getX() - 4.0f, lDarkness->getY() + 20.0f);
	vsDarkness->setMinValue(0.0f);
	vsDarkness->setMaxValue(1.0f);
	vsDarkness->setValue(lightDarkness);
	vsDarkness->setupHide(HT_HOROZONTAL, vsDarkness->getX() - 150.0f, .2f, true);
	
	// Make method boxes 
	method1Box.reset(1.0f, vsDarkness->getY() + 30.0f, menuWidth-2.0f, 77.0f);
	method2Box.reset(1.0f, method1Box.getY() + method1Box.getHeight() + 10.0f, menuWidth-2.0f, 35.0f);

	// Method 1 Checkbox 
	cbMethod1 = new UICheckbox(method1Box.getX(), method1Box.getY() + 5.0f,
		24.0f,24.0f,std::string("Use Method 1"));
	cbMethod1->setupHide(HT_HOROZONTAL,cbMethod1->getX()-150.0f,.2f,true);
	cbMethod1->setTextColor(.8f,.8f,.8f);
	cbMethod1->setChecked(true);

	// Create ray count label 
	lRayCount = new UILabel(std::string("Ray Count: 180"));
	lRayCount->setLocation(cbMethod1->getX() + 12.0f, cbMethod1->getY() + 30.0f);
	lRayCount->setTextSize(16.0f);
	lRayCount->setColor(.8f,.8f,.8f,1.0f);
	lRayCount->setupHide(HT_HOROZONTAL,lRayCount->getX()-150.0f,.2f,true);
	// Create ray count value slider 
	vsRayCount = new UIValueSlider();
	vsRayCount->setLocation(lRayCount->getX() - 4.0f, lRayCount->getY() + 20.0f);
	vsRayCount->setMinValue(5.0f);
	vsRayCount->setMaxValue(300.0f);
	vsRayCount->setValue(180.0f);
	vsRayCount->setupHide(HT_HOROZONTAL, vsRayCount->getX() - 150.0f, .2f, true);
	
	// Method 2 Checkbox 
	cbMethod2 = new UICheckbox(method2Box.getX(), method2Box.getY() + 5.0f,
		24.0f,24.0f,std::string("Use Method 2"));
	cbMethod2->setupHide(HT_HOROZONTAL,cbMethod2->getX()-150.0f,.2f,true);
	cbMethod2->setTextColor(.8f,.8f,.8f);
	cbMethod2->setChecked(false);
	
	lLightSize->setHidden();
	vsLightSize->setHidden();
	lRayCount->setHidden();
	vsRayCount->setHidden();
	lDarkness->setHidden();
	vsDarkness->setHidden();
	cbMethod1->setHidden();
	cbMethod2->setHidden();

	// Add corners
	tlC.setLocation(0.0f,0.0f);
	trC.setLocation(screen_width, 0.0f);
	blC.setLocation(0.0f, screen_height);
	brC.setLocation(screen_width, screen_height);
	lMap.addPoint(&tlC);
	lMap.addPoint(&trC);
	lMap.addPoint(&blC);
	lMap.addPoint(&brC);

	lMap.bHand = bHand;
}

// Load screen
// Note: If textures need to be loaded, they must
// be loaded in this method or they will not work. 
void LightScreen::load(TextureAtlas* mAtlas){
	UIScreen::load(mAtlas);

	UIAtlas* mUI = (UIAtlas*)mAtlas;
	bShow->centerText(mUI->mTextRender);
	bHide->centerText(mUI->mTextRender);
	bMove->centerText(mUI->mTextRender);
	bAdd->centerText(mUI->mTextRender);
	bRemove->centerText(mUI->mTextRender);
	bClear->centerText(mUI->mTextRender);
	bSetLight->centerText(mUI->mTextRender);

	show();
}

// Unload screen textures
// THIS MUST BE CALLED IF YOU LOAD STUFF.
void LightScreen::unload(){
	UIScreen::unload();
}

// Update the state of the screen
void LightScreen::update(float deltaTime){
	UIScreen::update(deltaTime);

	lTitle->update(deltaTime);
	bShow->update(deltaTime);
	bHide->update(deltaTime);
	bMove->update(deltaTime);
	bSetLight->update(deltaTime);
	bAdd->update(deltaTime);
	bRemove->update(deltaTime);
	bClear->update(deltaTime);
	cbShowLight->update(deltaTime);
	lLightSize->update(deltaTime);
	vsLightSize->update(deltaTime);
	lRayCount->update(deltaTime);
	vsRayCount->update(deltaTime);
	lDarkness->update(deltaTime);
	vsDarkness->update(deltaTime);
	cbMethod1->update(deltaTime);
	cbMethod2->update(deltaTime);

	lMap.update(deltaTime);
}

// Update input to the screen 
void LightScreen::updateInput(KeyHandler* mKeyH, MouseHandler* mMouseH){
	UIScreen::updateInput(mKeyH, mMouseH);

	// Update UI Based on state 
	if (screenShown)
	{
		// Update move state
		if (state == LSTATE_MOVE){
			if (subState == SMOVE_START){
				// Check for click and make sure not clicking on menu 
				if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown()
					&& mMouseH->getX() > menuWidth)
				{
					x1 = clampX(mMouseH->getX());
					y1 = clampY(mMouseH->getY());

					// Check if clicking box
					Box* b = bHand->contains(x1, y1);
					if (b != NULL){
						moveBox = b;
						subState = SMOVE_BOX;
						lTitle->setText(getStateString());
						return;
					}
				}
			}
			else if (subState == SMOVE_BOX){
				// Check for release 
				if (!mMouseH->isLeftDown()){
					moveBox = NULL;
					subState = SMOVE_START;
					lTitle->setText(getStateString());
					return;
				}

				// Get distance change 
				x2 = clampX(mMouseH->getX()) - x1;
				y2 = clampY(mMouseH->getY()) - y1;

				// Check if valid 
				bool validMove = true;
				if (!validX(moveBox->getX() + x2) ||
					!validX(moveBox->getX() + moveBox->getWidth() + x2) ||
					!validY(moveBox->getY() + y2) ||
					!validY(moveBox->getY() + moveBox->getHeight() + y2))
					validMove = false;
				
				// Move if valid 
				if (validMove){
					moveBox->setLocation(moveBox->getX() + x2, moveBox->getY() + y2);
					lMap.invalidate();
				}

				// Set old location 
				x1 = clampX(mMouseH->getX());
				y1 = clampY(mMouseH->getY());

				return;
			}
		}
		// Update add state 
		else if (state == LSTATE_ADD){
			if (subState == SADD_START){
				// Check for click and make sure not clicking on menu 
				if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown() 
					&& mMouseH->getX() > menuWidth)
				{
					x1 = x2 = clampX(mMouseH->getX());
					y1 = y2 = clampY(mMouseH->getY());
					subState = SADD_DRAG;
					lTitle->setText(getStateString());
				}
			}
			else if (subState == SADD_DRAG){
				x2 = clampX(mMouseH->getX());
				y2 = clampY(mMouseH->getY());

				// Check for release 
				if (!mMouseH->isLeftDown() && mMouseH->wasLeftDown())
				{
					addBox(std::min(x1,x2), std::min(y1,y2), abs(x1-x2), abs(y1-y2));
					subState = SADD_START;
					lTitle->setText(getStateString());
				}
			} 
		}
		// Update remove state 
		else if (state == LSTATE_REMOVE){
			if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown()){
				removeBox(bHand->contains(mMouseH->getX(), mMouseH->getY()));
			}
		}
		// Update set light
		else if (state == LSTATE_SETLIGHT){
			if (mMouseH->isLeftDown() && mMouseH->getX() > menuWidth){
				lMap.setLightLoc(
					clampX(mMouseH->getX()), clampY(mMouseH->getY()));
			}
		}

		// Swap screen states
		bMove->updateInput(mKeyH, mMouseH);
		if (bMove->wasClicked()){
			state = LSTATE_MOVE;
			subState = SMOVE_START;
			lTitle->setText(getStateString());
		}
		bAdd->updateInput(mKeyH, mMouseH);
		if (bAdd->wasClicked()){
			state = LSTATE_ADD;
			subState = SADD_START;
			lTitle->setText(getStateString());
		}
		bRemove->updateInput(mKeyH, mMouseH);
		if (bRemove->wasClicked()){
			state = LSTATE_REMOVE;
			lTitle->setText(getStateString());
		}
		bSetLight->updateInput(mKeyH, mMouseH);
		if (bSetLight->wasClicked()){
			state = LSTATE_SETLIGHT;
			lTitle->setText(getStateString());
		}
		
		// Check for clear boxes
		bClear->updateInput(mKeyH, mMouseH);
		if (bClear->wasClicked()){
			bHand->clear();
			lMap.clear();

			// Readd corners 
			lMap.addPoint(&tlC);
			lMap.addPoint(&trC);
			lMap.addPoint(&blC);
			lMap.addPoint(&brC);
		}

		// Check for show light
		cbShowLight->updateInput(mKeyH, mMouseH);
		drawLight = cbShowLight->Checked();

		// Update light size
		vsLightSize->updateInput(mKeyH, mMouseH);
		if (abs(vsLightSize->getValue() - lMap.getLightSize()) > 0.000001f){
			lMap.setLightSize(vsLightSize->getValue());
			if (state != LSTATE_CHANGE_LIGHT_SIZE){
				state = LSTATE_CHANGE_LIGHT_SIZE;
				lTitle->setText(getStateString());
			}
		}

		// Update ray count
		vsRayCount->updateInput(mKeyH, mMouseH);
		if (abs((int)vsRayCount->getValue() - lMap.getRayCount()) > 0.000001f){
			lMap.setRayCount((int)vsRayCount->getValue());
			lRayCount->setText(std::string("Ray Count: ") + toString(lMap.getRayCount()));
			if (state != LSTATE_CHANGE_LIGHT_SIZE){
				state = LSTATE_CHANGE_LIGHT_SIZE;
				lTitle->setText(getStateString());
			}
		}

		// Update darkness 
		vsDarkness->updateInput(mKeyH, mMouseH);
		if (abs(vsDarkness->getValue() - lightDarkness) > 0.000001f){
			lightDarkness = vsDarkness->getValue();
			if (state != LSTATE_DARKNESS){
				state = LSTATE_DARKNESS;
				lTitle->setText(getStateString());
			}
		}

		// Update checkboxes
		cbMethod1->updateInput(mKeyH, mMouseH);
		if (cbMethod1->CheckChanged()){
			cbMethod2->setChecked(!cbMethod1->Checked());
			lMap.setMethod1(cbMethod1->Checked());
			lMap.invalidate();
		}
		cbMethod2->updateInput(mKeyH, mMouseH);
		if (cbMethod2->CheckChanged()){
			cbMethod1->setChecked(!cbMethod2->Checked());
			lMap.setMethod1(!cbMethod2->Checked());
			lMap.invalidate();
		}

		// Check for hide screen
		bHide->updateInput(mKeyH, mMouseH);
		if (bHide->wasClicked()) hide();
	}
	else {
		// Check for show screen
		bShow->updateInput(mKeyH, mMouseH);
		if (bShow->wasClicked()) show();
	}
}

// Draw the screen
void LightScreen::draw(GLHandler* mgl, TextureAtlas* mAtlas){
	UIScreen::draw(mgl, mAtlas);
	
	// Set proj matrix 
	mgl->setProjectionMatrix(mgl->orthoMatrix);

	// Draw lights
	if (drawLight){
		float value = .5f * (1.0f - lightDarkness);
		mgl->lightBegin(value,value,value);
		lMap.drawMap(mgl);
		mgl->lightEnd();
	}
	
	// Bind UI Matrix's
	mAtlas->bindBuffers(mgl);
	mAtlas->bindTexture(mgl);

	// Enable light 
	if (drawLight) 
		mgl->enableLight(true);

	mgl->setFlatColor(0.875f, 0.875f, 0.875f, 1.0f);
	((UIAtlas*)mAtlas)->drawScale2(mgl, UII_REC, 0.0f,0.0f,screen_width, screen_height);
	// Draw boxes 
	bHand->draw(mgl, (UIAtlas*)mAtlas);
	mgl->enableLight(false);

	// State specific things 
	drawState(mgl, (UIAtlas*)mAtlas);

	//---------------------
	// Draw UI 
	
	// Map debug  
	lMap.drawDebug(mgl, (UIAtlas*)mAtlas);
	// Menu line 
	mgl->setFlatColor(.0f,.0f,.0f,bMove->getOpacity());
	((UIAtlas*)mAtlas)->drawScale2(mgl, UII_REC, 0.0f,0.0f,menuWidth+1.0f, screen_height);
	// Menu Background
	mgl->setFlatColor(.19f,.2f,.2f,bMove->getOpacity());
	((UIAtlas*)mAtlas)->drawScale2(mgl, UII_REC, 0.0f,0.0f,menuWidth, screen_height);
	// Draw method boxes 
	mgl->setFlatColor(.25f,.25f,.25f,bMove->getOpacity());
	((UIAtlas*)mAtlas)->drawScale2(mgl, UII_REC, method1Box.getX(), method1Box.getY(),
		method1Box.getWidth(), method1Box.getHeight());
	((UIAtlas*)mAtlas)->drawScale2(mgl, UII_REC, method2Box.getX(), method2Box.getY(),
		method2Box.getWidth(), method2Box.getHeight());

	// Draw buttons
	lTitle->draw(mgl, (UIAtlas*)mAtlas);
	bShow->draw(mgl, (UIAtlas*)mAtlas);
	bHide->draw(mgl, (UIAtlas*)mAtlas);
	bMove->draw(mgl, (UIAtlas*)mAtlas);
	bSetLight->draw(mgl, (UIAtlas*)mAtlas);
	bAdd->draw(mgl, (UIAtlas*)mAtlas);
	bRemove->draw(mgl, (UIAtlas*)mAtlas);
	bClear->draw(mgl, (UIAtlas*)mAtlas);
	cbShowLight->draw(mgl, (UIAtlas*)mAtlas);
	lLightSize->draw(mgl, (UIAtlas*)mAtlas);
	vsLightSize->draw(mgl, (UIAtlas*)mAtlas);
	lRayCount->draw(mgl, (UIAtlas*)mAtlas);
	vsRayCount->draw(mgl, (UIAtlas*)mAtlas);
	lDarkness->draw(mgl, (UIAtlas*)mAtlas);
	vsDarkness->draw(mgl, (UIAtlas*)mAtlas);
	cbMethod1->draw(mgl, (UIAtlas*)mAtlas);
	cbMethod2->draw(mgl, (UIAtlas*)mAtlas);
}

// Draw state 
void LightScreen::drawState(GLHandler* mgl, UIAtlas* mUI){
	if (state == LSTATE_ADD && subState == SADD_DRAG){
		mgl->setFlatColor(.1f,.1f,.1f,1.0f);
		mUI->drawScale2(mgl, UII_REC,std::min(x1,x2), std::min(y1,y2), abs(x1-x2), abs(y1-y2));
	}
}

// Hide the entire screen.
// Any UI elements will need to be put into this function,
// if they should be hidden when the screen is hidden.
void LightScreen::hide(){
	UIScreen::hide();

	lTitle->hide();
	bShow->show();
	bHide->hide();
	bMove->hide();
	bAdd->hide();
	bRemove->hide();
	bClear->hide();
	cbShowLight->hide();
	lLightSize->hide();
	vsLightSize->hide();
	bSetLight->hide();
	lRayCount->hide();
	vsRayCount->hide();
	lDarkness->hide();
	vsDarkness->hide();
	cbMethod1->hide();
	cbMethod2->hide();
	screenShown = false;
}

// Show the entire screen.
// All UI elements in the hide screen method should have show 
// calls here. 
void LightScreen::show(){
	UIScreen::show();
	
	lTitle->show();
	bHide->show();
	bShow->hide();
	bMove->show();
	bAdd->show();
	bRemove->show();
	bClear->show();
	cbShowLight->show();
	lLightSize->show();
	vsLightSize->show();
	bSetLight->show();
	lRayCount->show();
	vsRayCount->show();
	lDarkness->show();
	vsDarkness->show();
	cbMethod1->show();
	cbMethod2->show();
	screenShown = true;
}

// Add new box to list 
void LightScreen::addBox(float x, float y, float width, float height){
	if (height <= 1.0f || width <= 1.0f){
		std::cout << "ERROR: Cannot add box with width or height less than or equal to 1\n";
		return;
	}

	// add box 
	Box* b = bHand->add(x,y,width,height);
	b->setColor(.738f, .535f,.32f,1.0f);

	if (b != NULL){
		// Add corners 
		lMap.addPoint(b->getCornerTopLeft());
		lMap.addPoint(b->getCornerTopRight());
		lMap.addPoint(b->getCornerBottomLeft());
		lMap.addPoint(b->getCornerBottomRight());

		// Add walls 
		lMap.addSeg(Seg(b->getCornerTopLeft(), b->getCornerTopRight()));
		lMap.addSeg(Seg(b->getCornerTopRight(), b->getCornerBottomRight()));
		lMap.addSeg(Seg(b->getCornerBottomRight(), b->getCornerBottomLeft()));
		lMap.addSeg(Seg(b->getCornerBottomLeft(), b->getCornerTopLeft()));
	}
}

// Remove box from list 
void LightScreen::removeBox(Box* b){
	if (b == NULL) return;
	// Remove corners 
	lMap.removePoint(b->getCornerTopLeft());
	lMap.removePoint(b->getCornerTopRight());
	lMap.removePoint(b->getCornerBottomLeft());
	lMap.removePoint(b->getCornerBottomRight());

	// Remove walls 
	lMap.removeSeg(Seg(b->getCornerTopLeft(), b->getCornerTopRight()));
	lMap.removeSeg(Seg(b->getCornerTopRight(), b->getCornerBottomRight()));
	lMap.removeSeg(Seg(b->getCornerBottomRight(), b->getCornerBottomLeft()));
	lMap.removeSeg(Seg(b->getCornerBottomLeft(), b->getCornerTopLeft()));

	// Remove box 
	bHand->remove(b);
}

// Clamp x add location 
int LightScreen::clampX(float x){
	if (x < menuWidth)
		return menuWidth;
	if (x > screen_width)
		return screen_width;
	return x;
}
// Clamp y add location
int LightScreen::clampY(float y){
	if (y < 0.0f)
		return 0.0f;
	if (y > screen_height)
		return screen_height;
	return y;
}

// Check if valid x loc
bool LightScreen::validX(float x){
	if (x < menuWidth)
		return false;
	if (x > screen_width)
		return false;
	return true;
}
// Check if valid y loc
bool LightScreen::validY(float y){
	if (y < 0.0f)
		return false;
	if (y > screen_height)
		return false;
	return true;
}

// Get string for state 
std::string LightScreen::getStateString(){
	switch (state){
	case LSTATE_MOVE:
		switch (subState){
		case SMOVE_START:
			return std::string("State: Move Object Select");
		case SMOVE_BOX:
			return std::string("State: Move Box");
		}
		break;
	case LSTATE_ADD:
		switch (subState){
		case SADD_START:
			return std::string("State: Add Object Start");
		case SADD_DRAG:
			return std::string("State: Add Object Drag");
		}
		break;
	case LSTATE_REMOVE:
		return std::string("State: Remove Object");
	case LSTATE_SETLIGHT:
		return std::string("State: Move Light");
	case LSTATE_CHANGE_LIGHT_SIZE:
		return std::string("State: Change light size");
	case LSTATE_CHANGE_RAY_COUNT:
		return std::string("State: Change ray count");
	case LSTATE_DARKNESS:
		return std::string("State: Change darkness value");
	default:
		return std::string("");
	}
}