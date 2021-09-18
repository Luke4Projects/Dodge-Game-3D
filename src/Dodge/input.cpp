#include "game.h"
#include <glad/glad.h>

//
// calls input and event functions
//
void Game::DoInput() {

	// poll SDL events
	SDL_PollEvent(&event);

	// SDL events
	switch (event.type) {
	case SDL_QUIT:
		runningApp = false;
		break;
	}
	switch (event.window.event) {
	case SDL_WINDOWEVENT_RESIZED:
		resizeEvent();
		break;
	}

	// update delta time
	float currentFrame = SDL_GetTicks();
	deltaTime = (currentFrame - lastFrameTick) / 10;
	lastFrameTick = currentFrame;

	// call looped input functions
	KeyboardInput();

}

//
// this has all code for user input by using the keyboard, called every frame
//
void Game::KeyboardInput() {

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	float moveSpeed = deltaTime/50.f;
	if (keystate[SDL_SCANCODE_D]) {
		playerPos.x += moveSpeed;
	}	
	if (keystate[SDL_SCANCODE_A]) {
		playerPos.x -= moveSpeed;
	}

}

void Game::resizeEvent() {
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
}