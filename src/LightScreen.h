#pragma once
#include <math.h>
#include <stdlib.h>
#include "UIScreen.h"
#include "UIButton.h"
#include "BoxHandler.h"

// States
#define LSTATE_MOVE 0
#define LSTATE_ADD 1
#define LSTATE_REMOVE 2

// Adding sub states
#define SADD_START 0
#define SADD_DRAG 1

class LightScreen : public UIScreen
{
	// Menu Values
	float menuWidth;

	// States 
	bool screenShown;
	bool drawLight;
	int state;
	int subState;

	// List of boxes 
	BoxHandler* bHand;

	// Add state variables 
	float x1,x2,y1,y2;

	// UI Components
	UIButton* bShow;
	UIButton* bHide;
	UIButton* bMove;
	UIButton* bAdd;
	UIButton* bRemove;

public:
	LightScreen();
	virtual ~LightScreen();
	
	// Initialize screen
	virtual void init(float screen_width, float screen_height);

	// Load screen
	// Note: If textures need to be loaded, they must
	// be loaded in this method or they will not work. 
	virtual void load(TextureAtlas* mAtlas);

	// Unload screen textures
	// THIS MUST BE CALLED IF YOU LOAD STUFF.
	virtual void unload();

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Draw state 
	void drawState(GLHandler* mgl, UIAtlas* mUI);

	// Hide the entire screen.
	// Any UI elements will need to be put into this function,
    // if they should be hidden when the screen is hidden.
	virtual void hide();

	// Show the entire screen.
	// All UI elements in the hide screen method should have show 
	// calls here. 
	virtual void show();

	// Add new box to list 
	void addBox(float x, float y, float width, float height);

	// Remove box from list 
	void removeBox(Box* box);
};

