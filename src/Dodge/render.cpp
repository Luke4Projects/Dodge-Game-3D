#include <glad/glad.h>
#include "game.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//
// has all rendering code, called every frame
//
void Game::RenderGame() {

	UpdateMatrices(); // update projection and view matrices

	// create obstacle if it has been long enough
	lastObstacleCreated += deltaTime;
	if (lastObstacleCreated >= 30.f) {
		createObstacle();
		lastObstacleCreated = 0.f;
	}

	// clear the window blue
	glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw the floor
	floorPos += deltaTime / 100.f;
	glm::mat4 texModel = glm::translate(glm::mat4(1.f), glm::vec3(0, floorPos, 0));
	texModel = glm::scale(texModel, glm::vec3(10.f, 10.f, 10.f));
	glUniformMatrix4fv(glGetUniformLocation(shapeRenderer.shader, "textureMatrix"), 1, GL_FALSE, glm::value_ptr(texModel));
	shapeRenderer.DrawCube(textures[1], glm::vec3(0.f, -1.f, 0.f), glm::vec3(50.f, 1.f, 50.f), glm::vec3(0.f));
	glUniformMatrix4fv(glGetUniformLocation(shapeRenderer.shader, "textureMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	// draw the player
	shapeRenderer.DrawCube(textures[0], playerPos, glm::vec3(1.f), glm::vec3(0.f));

	// draw the obstacles
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].pos.z += deltaTime / 10.f;
		shapeRenderer.DrawCube(textures[0], obstacles[i].pos, glm::vec3(1.f), glm::vec3(0.f));
	}

}

//
// updates the projection and view matrices for all shaders
//
void Game::UpdateMatrices() {

	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), camera.pos);

	glUseProgram(shapeRenderer.shader);
	glUniformMatrix4fv(glGetUniformLocation(shapeRenderer.shader, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shapeRenderer.shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shapeRenderer.shader, "textureMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

}