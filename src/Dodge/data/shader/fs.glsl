#version 330 core

out vec4 FragColor;

in vec4 texCoord;
uniform sampler2D texture1;

void main() {
	FragColor = texture(texture1, vec2(texCoord));
}