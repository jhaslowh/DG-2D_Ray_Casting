#pragma once
#include <string>
#include <iostream>
#include "GLHandler.h"
#include "TextRender.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "TextureAtlas.h"
#include "FileHelper.h"

class UIScreen
{
protected:
	bool loaded;		// True when screen has been loaded 
	bool unloaded;		// True when screen has been unloaded
public:
	UIScreen();
	virtual ~UIScreen();

	// Initialize screen
	virtual void init(float screen_width, float screen_height);

	// Load screen
	// Note: If textures need to be loaded, they must
	// be loaded in this method or they will not work. 
	virtual void load(TextureAtlas* mAtlas);

	// Unload screen textures
	// THIS MUST BE CALLED IF YOU LOAD STUFF.
	virtual void unload();
	bool isUnloaded();

	// Update the state of the screen
	virtual void update(float deltaTime);

	// Update input to the screen 
	virtual void updateInput(KeyHandler*, MouseHandler*);

	// Draw the screen
	virtual void draw(GLHandler* mgl, TextureAtlas* mAtlas);

	// Hide the entire screen.
	// Any UI elements will need to be put into this function,
    // if they should be hidden when the screen is hidden.
	virtual void hide();

	// Show the entire screen.
	// All UI elements in the hide screen method should have show 
	// calls here. 
	virtual void show();
};

