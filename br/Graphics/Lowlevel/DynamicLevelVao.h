#pragma once

#include <GL\glew.h>
#include "IndexedVertexArray.h"
#include <vector>

using std::vector;

class DynamicLevelVao : public IndexedVertexArray
{
public:
	DynamicLevelVao(GLfloat* vertices, GLuint* indices, GLint numVerts, GLint indicesCount, GLint floatPerVertex);
	~DynamicLevelVao();

	void modifyTexBuffers(GLfloat* texCoords1, GLfloat* texCoords2, int num);
	void modifyTranslationBuffer(GLfloat* coords, int num);
	void modifyIdBuffer(GLfloat* ids, int num);

	void drawInstances(int num);

private:
	GLuint texVbo1, texVbo2;
	GLuint translationVbo;
	GLuint idVbo;

	void setupVBOs();
};

