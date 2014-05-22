#pragma once

// Using the standard output for printf 
#include <stdio.h>
#include <stdlib.h>
#include <vector>
// Use glew.h instead of gl.h to get all the GL prototypes declared 
#include <glew.h>
// Using the SDL library for the base windowing setup 
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_timer.h>

#include "GLHandler.h"
#include "UIAtlas.h"
#include "KeyHandler.h"
#include "MouseHandler.h"

#include "UIScreen.h"
#include "LightScreen.h"

bool WINDOW_VISIBLE = false;

/// Game loop and FPS timing 
int FPS = 60;				// number of frames per second
int MAX_FRAME_SKIPS = 12;	// maximum number of frames to be skipped
int FRAME_PERIOD = 1000/FPS;// the number of milliseconds per frame
int lastTime = 0;			
float deltaTime = 0;		// Used in game loop to tell how much time has passed
float SCREEN_WIDTH = 1280.0f;
float SCREEN_HEIGHT = 720.0f;

// States 
bool running = true;		
bool render = false;        // Set to true each time game needs to be rendered 

// Handlers
GLHandler mgl;
KeyHandler mKeyH;
MouseHandler mMouseH;
UIAtlas* mUIAtlas;

// GUI Stuff
SDL_Window* window;
SDL_Thread* thread;
UIScreen* screen = NULL;
bool showTerminal = false;

// Called at the begining of the game to load resources 
int init_resources();

// Called when finished to free resources
void free_resources();

// Update game state
void onUpdate();

// Render game to screen 
void onDraw();

// Game loop to update game state
int gameLoop(void*);

// Updates window events and renders screen.
void eventAndRenderLoop();

// Game a new game 
void createGame();
