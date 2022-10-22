#include "Plane.h"

#include "../../../utils/Debug.h";

Plane::Plane() : Plane("Unnamed Plane") {}

Plane::Plane(const std::string& name) : Plane(name, { 1.0f, 1.0f }) {}

Plane::Plane(const std::string& name, const glm::vec2& size) : Plane(name, size, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }) {}

Plane::Plane(const std::string& name, const glm::vec2& size, const glm::vec3& position, const glm::vec3& rotation) : Model(name, position, rotation), size(size)
{
	create();
}

void Plane::setShader(Shader* shader)
{
	Model::setShader(shader);
}

const glm::vec2& Plane::getSize() const
{
	return size;
}

void Plane::create()
{
	float vertices[] = {
		-size.x / 2.0f, -size.y / 2.0f, 0.0f,
		-size.x / 2.0f,  size.y / 2.0f, 0.0f,
		 size.x / 2.0f,  size.y / 2.0f, 0.0f,
		 size.x / 2.0f, -size.y / 2.0f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	float uv[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	setVertexArray(new VertexArray(vertices, sizeof(vertices), indices, sizeof(indices), uv, sizeof(uv)));
}
