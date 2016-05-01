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

	void modifyTexBuffers(vector<GLfloat>& texCoords1, vector<GLfloat>& texCoords2, int num);

	void drawInstances(int num);

private:
	GLuint texVbo1, texVbo2;

	void setupVBOs();
};

