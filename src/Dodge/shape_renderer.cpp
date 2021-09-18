#include "shape_renderer.h"
#include "shader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//
// calls all initialization functions
//
void ShapeRenderer::Init() {

	// load shaders
	shader = loadShader("data/shader/vs.glsl", "data/shader/fs.glsl");

	// set VAO's
	SetCubeVAO();

}

//
// Draws a shape with the Cube VAO
//
void ShapeRenderer::DrawCube(unsigned int texture, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation) {

	glUseProgram(shader);

	// transform
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

	// render
	glBindVertexArray(VAO_cube);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

//
// sets the VAO_cube variable value
//
void ShapeRenderer::SetCubeVAO() {

	float vertices[] = {
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,        
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
        // Left face
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
        // Right face
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,     
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  
	};

	unsigned int VBO;
	glGenVertexArrays(1, &VAO_cube);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO_cube);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

}