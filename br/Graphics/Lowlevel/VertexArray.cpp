#include "VertexArray.h"
#include "../Shaders/Shader.h"

VertexArray::VertexArray(GLfloat* vertices, GLint count, GLint floatPerVertex) {
	tbo = 0;
	this->count = count;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, floatPerVertex * count * sizeof GLfloat, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::VERTEX_ATTRIB_LOC, floatPerVertex, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::VERTEX_ATTRIB_LOC);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	delete[] vertices;
}

VertexArray::VertexArray(GLfloat* texCoords, GLfloat* vertices, GLint numVerts, GLint numTex, GLint floatPerVertex) {
	this->count = count;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, floatPerVertex * numVerts * sizeof GLfloat, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::VERTEX_ATTRIB_LOC, floatPerVertex, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::VERTEX_ATTRIB_LOC);

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * numTex * sizeof GLfloat, texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::TEX_ATTRIB_LOC, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::TEX_ATTRIB_LOC);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	delete[] texCoords;
	delete[] vertices;
}

void VertexArray::bind() {
	glBindVertexArray(vao);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::draw() {
	bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
	unbind();
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	if (tbo != 0)
		glDeleteBuffers(1, &tbo);
}
