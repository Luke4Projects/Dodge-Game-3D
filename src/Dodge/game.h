#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <vector>
#include "shape_renderer.h";
#include "camera.h";
#include "obstacle.h";

class Game {
public:
	int Init();
	void RunMainLoop();
	void Cleanup();
private:

	SDL_Window* window;
	SDL_GLContext gl_context;
	SDL_Event event;

	ShapeRenderer shapeRenderer;
	Camera camera;

	std::vector<unsigned int> textures;
	std::vector<Obstacle> obstacles;

	bool runningApp;
	float deltaTime;
	float lastFrameTick;
	int windowWidth, windowHeight;

	glm::vec3 playerPos;
	float floorPos;

	float lastObstacleCreated;

	void loadResources();

	void createObstacle();

	void RenderGame();
	void UpdateMatrices();

	void DoInput();
	void KeyboardInput();
	void resizeEvent();

};

#endif