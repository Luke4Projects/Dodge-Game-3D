#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <glm/glm.hpp>

class ShapeRenderer {
public:
	void Init();
	void DrawCube(unsigned int texture, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation);
	unsigned int shader;
private:
	unsigned int VAO_cube;
	void SetCubeVAO();
};

#endif