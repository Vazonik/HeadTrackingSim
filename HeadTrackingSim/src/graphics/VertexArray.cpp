#include "VertexArray.h"
#include <glad/glad.h>

unsigned int VertexArray::VERTEX_ATTRIB = 0;
unsigned int VertexArray::TCOORD_ATTRIB = 1;

VertexArray::VertexArray() : vao(0), vbo(0), tbo(0), ibo(0), count(0), mode(Solid) {}

VertexArray::VertexArray(float vertices[], size_t verticesSize, unsigned int indices[], size_t indicesSize, float uv[], size_t uvSize, DrawMode mode) : VertexArray()
{
	this->mode = mode;

	if (indices == nullptr)
	{
		this->count = verticesSize / sizeof(float);
	}
	else
	{
		this->count = indicesSize / sizeof(unsigned int);
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_ATTRIB);

	if (uv != nullptr)
	{
		glGenBuffers(1, &tbo);
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
		glBufferData(GL_ARRAY_BUFFER, uvSize, uv, GL_STATIC_DRAW);
		glVertexAttribPointer(TCOORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TCOORD_ATTRIB);
	}

	if (indices != nullptr)
	{
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VertexArray::VertexArray(float vertices[], size_t verticesSize, unsigned int indices[], size_t indicesSize, DrawMode mode)
	: VertexArray(vertices, verticesSize, indices, indicesSize, nullptr, 0, mode)
{}

VertexArray::VertexArray(float vertices[], size_t verticesSize, DrawMode mode)
	: VertexArray(vertices, verticesSize, nullptr, 0, nullptr, 0, mode)
{}

void VertexArray::bind()
{
	glBindVertexArray(vao);
	if (ibo > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	}
}

void VertexArray::unbind()
{
	if (ibo > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

void VertexArray::draw()
{
	if (ibo > 0) {
		glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(mode, 0, count);
	}
}

void VertexArray::render()
{
	bind();
	draw();
}


