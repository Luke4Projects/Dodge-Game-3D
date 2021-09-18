#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec4 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 textureMatrix;

void main() {
	texCoord = textureMatrix * vec4(aTexCoord, 1.0, 1.0);
	gl_Position = proj * view * model * vec4(aPos, 1.0);
}