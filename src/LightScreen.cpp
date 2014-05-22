#include "LightScreen.h"


LightScreen::LightScreen() : UIScreen()
{
	// Screen values
	screen_width = screen_height = 0.0f;

	// Menu Values
	menuWidth = 150.0f;

	// States 
	screenShown = true;
	drawLight = false;
	state = LSTATE_MOVE;
	subState = SMOVE_START;

	// Create box handler
	bHand = new BoxHandler(100);

	// Move state variables 
	moveBox = NULL;

	// Add state variables 
	x1 = x2 = y1 = y2 = 0.0f;

	// UI Components 
	bShow = NULL;
	bHide = NULL;
	bMove = NULL;
	bAdd = NULL;
	bRemove = NULL;
	lTitle = NULL;
}

LightScreen::~LightScreen()
{
	delete bShow;
	bShow = NULL;
	delete bHide;
	bHide = NULL;
	delete bMove;
	bMove = NULL;
	delete bAdd;
	bAdd = NULL;
	delete bRemove;
	bRemove = NULL;
	delete bHand;
	bHand = NULL;
	delete lTitle;
	lTitle = NULL;
}
	
// Initialize screen
void LightScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	this->screen_width = screen_width;
	this->screen_height = screen_height;
	float spacing = 5.0f;

	// Create title 
	lTitle = new UILabel(getStateString());
	lTitle->setLocation(menuWidth + 10.0f, 10.0f);
	lTitle->setTextSize(25.0f);
	lTitle->setColor(.5f,.5f,.5f,1.0f);
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
	// Create add button 
	bAdd = new UIButton(10.0f,50.0f,100.0f,35.0f, std::string("Add"));
	bAdd->setupHide(HT_HOROZONTAL,bAdd->getX()-150.0f,.2f,true);
	bAdd->setHidden();
	// Create remove button 
	bRemove = new UIButton(10.0f,90.0f,100.0f,35.0f, std::string("Remove"));
	bRemove->setupHide(HT_HOROZONTAL,bRemove->getX()-150.0f,.2f,true);
	bRemove->setHidden();
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
	bAdd->update(deltaTime);
	bRemove->update(deltaTime);
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

					// TODO check for click on light 
				}
			}
			else if (subState == SMOVE_BOX){
				// Check for release 
				if (!mMouseH->isLeftDown() && mMouseH->wasLeftDown())
				{
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
					moveBox->setLocation(
						moveBox->getX() + x2,
						moveBox->getY() + y2);
				}

				// Set old location 
				x1 = clampX(mMouseH->getX());
				y1 = clampY(mMouseH->getY());
			}
			else if (subState == SMOVE_LIGHT){
				// TODO 
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
		mgl->lightBegin(0.0f,0.0f,0.0f);
		// TODO Draw light
		mgl->lightEnd();
	}

	// Bind UI Matrix's
	mAtlas->bindBuffers(mgl);
	mAtlas->bindTexture(mgl);

	// Draw map 
	if (drawLight) 
		mgl->enableLight(true);
	bHand->draw(mgl, (UIAtlas*)mAtlas);
	mgl->enableLight(false);

	drawState(mgl, (UIAtlas*)mAtlas);

	// Draw UI 
	mgl->setFlatColor(.0f,.0f,.0f,bMove->getOpacity());
	((UIAtlas*)mAtlas)->drawScale2(mgl, UII_REC, 0.0f,0.0f,menuWidth+1.0f, screen_height);
	mgl->setFlatColor(.19f,.2f,.2f,bMove->getOpacity());
	((UIAtlas*)mAtlas)->drawScale2(mgl, UII_REC, 0.0f,0.0f,menuWidth, screen_height);

	// Draw buttons
	lTitle->draw(mgl, (UIAtlas*)mAtlas);
	bShow->draw(mgl, (UIAtlas*)mAtlas);
	bHide->draw(mgl, (UIAtlas*)mAtlas);
	bMove->draw(mgl, (UIAtlas*)mAtlas);
	bAdd->draw(mgl, (UIAtlas*)mAtlas);
	bRemove->draw(mgl, (UIAtlas*)mAtlas);
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
	screenShown = true;
}

// Add new box to list 
void LightScreen::addBox(float x, float y, float width, float height){
	if (height <= 1.0f || width <= 1.0f){
		std::cout << "ERROR: Cannot add box with width or height less than or equal to 1\n";
		return;
	}

	// add box 
	bHand->add(x,y,width,height);

	// TODO add corners and walls to light map 
}

// Remove box from list 
void LightScreen::removeBox(Box* box){
	if (box == NULL) return;

	// TODO remove corners and walls from light map 

	// Remove box 
	bHand->remove(box);
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
		case SMOVE_LIGHT:
			return std::string("State: Move Light");
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
	default:
		return std::string("");
	}
}