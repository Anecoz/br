#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class VertexArray
{
public:
	VertexArray(GLfloat* vertices, GLint count, GLint floatPerVertex);
	VertexArray(GLfloat* texCoords, GLfloat* vertices, GLint vertCount, GLint texCount, GLint floatPerVertex);
	~VertexArray();

	void virtual draw();

	GLint getVAOID() { return vao; }
	GLint getCount() { return count; }

protected:
	GLuint vao, vbo, tbo;
	GLint count;

	void bind();
	void unbind();
};

