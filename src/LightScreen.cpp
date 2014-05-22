#include "LightScreen.h"


LightScreen::LightScreen() : UIScreen()
{
	// States 
	screenShown = true;
	drawLight = false;
	state = LSTATE_MOVE;
	subState = 0;

	// Create box handler
	bHand = new BoxHandler(100);

	// Add state variables 
	x1 = x2 = y1 = y2 = 0.0f;

	// UI Components 
	bShow = NULL;
	bHide = NULL;
	bMove = NULL;
	bAdd = NULL;
	bRemove = NULL;
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
}
	
// Initialize screen
void LightScreen::init(float screen_width, float screen_height){
	UIScreen::init(screen_width, screen_height);

	float spacing = 5.0f;

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
			// TODO 
		}
		// Update add state 
		else if (state == LSTATE_ADD){
			if (subState == SADD_START){
				// Check for click 
				if (mMouseH->isLeftDown() && !mMouseH->wasLeftDown())
				{
					x1 = mMouseH->getX();
					y1 = mMouseH->getY();
					subState = SADD_DRAG;
				}
			}
			else if (subState == SADD_DRAG){
				x2 = mMouseH->getX();
				y2 = mMouseH->getY();

				// Check for release 
				if (!mMouseH->isLeftDown() && mMouseH->wasLeftDown())
				{
					addBox(std::min(x1,x2), std::min(y1,y2), abs(x1-x2), abs(y1-y2));
					subState = SADD_START;
				}
			} 
		}
		// Update remove state 
		else if (state == LSTATE_REMOVE){
			// TODO 
		}

		// Swap screen states
		bMove->updateInput(mKeyH, mMouseH);
		if (bMove->wasClicked())
			state = LSTATE_MOVE;
		bAdd->updateInput(mKeyH, mMouseH);
		if (bAdd->wasClicked()){
			state = LSTATE_ADD;
			subState = SADD_START;
		}
		bRemove->updateInput(mKeyH, mMouseH);
		if (bRemove->wasClicked())
			state = LSTATE_REMOVE;

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
	// TODO remove corners and walls from light map 

	// Remove box 
	bHand->remove(box);
}