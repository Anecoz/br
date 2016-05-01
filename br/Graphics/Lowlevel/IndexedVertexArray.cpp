#include "IndexedVertexArray.h"

IndexedVertexArray::IndexedVertexArray(GLfloat* vertices, GLuint* indices, GLint numVerts, GLint indicesCount, GLint floatPerVertex)
: VertexArray(vertices, numVerts, floatPerVertex) {
	this->count = indicesCount;

	VertexArray::bind();

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);

	VertexArray::unbind();
	delete[] indices;
}

IndexedVertexArray::IndexedVertexArray(GLfloat* vertices, GLfloat* texCoords, GLuint* indices, GLint numVerts, GLint indicesCount, GLint texCount, GLint floatPerVertex)
	: VertexArray(texCoords, vertices, numVerts, texCount, floatPerVertex) {
	this->count = indicesCount;

	VertexArray::bind();

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);

	VertexArray::unbind();
	delete[] indices;
}

IndexedVertexArray::~IndexedVertexArray() {
	VertexArray::~VertexArray();
	glDeleteBuffers(1, &ibo);
}

void IndexedVertexArray::draw() {
	VertexArray::bind();

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0L);

	VertexArray::unbind();
}
