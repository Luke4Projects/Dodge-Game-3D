#include <glad/glad.h>
#include "game.h"
#include "shader.h"
#include <iostream>

//
// initializes variables and libraries, returns 0 if success
//
int Game::Init() {

	// initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "failed to init SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create SDL window
	int windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, windowFlags);
	if (window == NULL) {
		std::cout << "Failed to create SDL2 window: " << SDL_GetError << std::endl;
		return -1;
	}

	// Create OpenGL context
	gl_context = SDL_GL_CreateContext(window);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "failed to initialize GLAD opengl loader\n";
		return -1;
	}

	// options
	glEnable(GL_DEPTH_TEST);

	loadResources();

	// initialize variables
	playerPos = glm::vec3(0.f);
	floorPos = 0.f;
	windowWidth = 1280;
	windowHeight = 720;

	// initialize our shape renderer
	shapeRenderer.Init();

	return 0;
}

//
// loads textures and other resources
//
void Game::loadResources() {
	
	unsigned int texture = loadTexture("data/img/wall.jpg");
	textures.push_back(texture);	
	unsigned int texture2 = loadTexture("data/img/wall2.jpg");
	textures.push_back(texture2);

}

//
// starts the main game while loop, runs until window is closed
//
void Game::RunMainLoop() {

	runningApp = true;
	while (runningApp) {

		DoInput();
		RenderGame();

		// swap buffers
		SDL_GL_SwapWindow(window);

	}

}

//
// frees memory allocated by the game
//
void Game::Cleanup() {

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

//
// Adds a new obstacle to the obstacles vector
//
void Game::createObstacle() {

	float x = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 + 5)));
	Obstacle obstacle(glm::vec3(x, 0.f, -10.f));
	obstacles.push_back(obstacle);

}