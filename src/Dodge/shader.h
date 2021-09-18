#ifndef SHADER_H
#define SHADER_H

#include <string>

unsigned int loadShader(std::string vertexPath, std::string fragPath);
unsigned int loadTexture(const char* path);

#endif