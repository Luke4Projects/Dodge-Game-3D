#include "shader.h"
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

//
// returns a string loaded from a file
//
std::string loadFile(std::string path) {
	std::ifstream file(path);
	std::string fileData, line;
	while (std::getline(file, line)) {
		fileData += line + "\n";
	}
	return fileData;
}

//
// returns an opengl shader program with a vertex and fragment shader with source loaded from the path parameters
//
unsigned int loadShader(std::string vertexPath, std::string fragPath) {

	// load shader source from file
	std::string lv = loadFile(vertexPath);
	std::string lf = loadFile(fragPath);
	const char* vsource = const_cast<char*>(lv.c_str());
	const char* fsource = const_cast<char*>(lf.c_str());

	// create and compile shaders
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fsource, NULL);
	glCompileShader(vs);
	glCompileShader(fs);

	// create shader program
	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// delete shaders after adding them to program
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

//
// returns an opengl texture with data loaded from a file from the path parameter
//
unsigned int loadTexture(const char* path) {

	// create opengl texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image file and bind it to texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load image\n";
		return NULL;
	}

	return texture;
}