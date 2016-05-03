#include "DynamicLevelVao.h"
#include "../../Utils/GraphicsUtils.h"

DynamicLevelVao::DynamicLevelVao(GLfloat* vertices, GLuint* indices, GLint numVerts, GLint indicesCount, GLint floatPerVertex)
: IndexedVertexArray(vertices, indices, numVerts, indicesCount, floatPerVertex) {
	setupVBOs();
}

DynamicLevelVao::~DynamicLevelVao() {
	IndexedVertexArray::~IndexedVertexArray();
	//glDeleteBuffers(1, &texVbo1);
	//glDeleteBuffers(1, &texVbo2);
	glDeleteBuffers(1, &translationVbo);
	glDeleteBuffers(1, &idVbo);
}

void DynamicLevelVao::drawInstances(int num) {
	IndexedVertexArray::bind();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElementsInstanced(GL_TRIANGLES, this->count, GL_UNSIGNED_INT, 0, num);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	IndexedVertexArray::unbind();
}

void DynamicLevelVao::modifyTexBuffers(GLfloat* texCoords1, GLfloat* texCoords2, int num) {
	IndexedVertexArray::bind();	

	glBindBuffer(GL_ARRAY_BUFFER, texVbo1);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof GLfloat, texCoords1, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, texVbo2);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof GLfloat, texCoords2, GL_DYNAMIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IndexedVertexArray::unbind();
}

void DynamicLevelVao::modifyTranslationBuffer(GLfloat* coords, int num) {
	IndexedVertexArray::bind();

	glBindBuffer(GL_ARRAY_BUFFER, translationVbo);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof GLfloat, coords, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IndexedVertexArray::unbind();
}

void DynamicLevelVao::modifyIdBuffer(GLfloat* ids, int num) {
	IndexedVertexArray::bind();

	glBindBuffer(GL_ARRAY_BUFFER, idVbo);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof GLfloat, ids, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IndexedVertexArray::unbind();
}

void DynamicLevelVao::setupVBOs() {
	IndexedVertexArray::bind();
	/*glGenBuffers(1, &texVbo1);
	glBindBuffer(GL_ARRAY_BUFFER, texVbo1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glGenBuffers(1, &texVbo2);
	glBindBuffer(GL_ARRAY_BUFFER, texVbo2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);*/

	glGenBuffers(1, &translationVbo);
	glBindBuffer(GL_ARRAY_BUFFER, translationVbo);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

	glGenBuffers(1, &idVbo);
	glBindBuffer(GL_ARRAY_BUFFER, idVbo);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	IndexedVertexArray::unbind();
}
