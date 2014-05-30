#pragma once
#include <math.h>
#include <stdlib.h>
#include <string>
#include "UIScreen.h"
#include "UIButton.h"
#include "UILabel.h"
#include "UICheckbox.h"
#include "UIValueSlider.h"
#include "BoxHandler.h"
#include "LightMap.h"
#include "Point.h"

// States
#define LSTATE_MOVE 0
#define LSTATE_ADD 1
#define LSTATE_REMOVE 2
#define LSTATE_SETLIGHT 3
#define LSTATE_CHANGE_LIGHT_SIZE 4

// Move object states 
#define SMOVE_START 5
#define SMOVE_BOX 6

// Adding sub states
#define SADD_START 7
#define SADD_DRAG 8

class LightScreen : public UIScreen
{
	// Screen values
	float screen_width;
	float screen_height;

	// Menu Values
	float menuWidth;

	// States 
	bool screenShown;
	bool drawLight;
	int state;
	int subState;

	// Elements
	BoxHandler* bHand;
	LightMap lMap;

	// state variables 
	Box* moveBox;		// Box being moved 
	float x1,x2,y1,y2; // Location temps to use with mouse

	// UI Components
	UILabel* lTitle;
	UIButton* bShow;
	UIButton* bHide;
	UIButton* bMove;
	UIButton* bSetLight;
	UIButton* bAdd;
	UIButton* bRemove;
	UIButton* bClear;
	UICheckbox* cbShowLight;
	UILabel* lLightSize;
	UIValueSlider* vsLightSize;

	// Corners
	Point tlC, trC, blC, brC;

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

private:

	// Clamp x location 
	int clampX(float x);
	// Clamp y location
	int clampY(float y);

	// Check if valid x loc
	bool validX(float x);
	// Check if valid y loc
	bool validY(float y);

	// Get string for state 
	std::string getStateString();
};

