#include "GraphicsUtils.h"
#include <iomanip>

DynamicLevelVao* GraphicsUtils::createLevelQuad() {
	GLfloat* vertices = new GLfloat[8];
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;
	vertices[3] = 1.0f;
	vertices[4] = 1.0f;
	vertices[5] = 0.0f;
	vertices[6] = 1.0f;
	vertices[7] = 1.0f;

	GLuint* indices = new GLuint[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;

	return new DynamicLevelVao(vertices, indices, 4, 6, 2);
}

IndexedVertexArray* GraphicsUtils::createSimpleQuad() {
	GLfloat* vertices = new GLfloat[8];
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;
	vertices[3] = 1.0f;
	vertices[4] = 1.0f;
	vertices[5] = 0.0f;
	vertices[6] = 1.0f;
	vertices[7] = 1.0f;

	GLuint* indices = new GLuint[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;

	return new IndexedVertexArray(vertices, indices, 4, 6, 2);
}

GLuint GraphicsUtils::loadPNGToTexture(const char* fileName, unsigned& width, unsigned& height) {
	GLuint texId;
	//unsigned width, height;
	vector<unsigned char> image;
	unsigned error = lodepng::decode(image, width, height, fileName);

	if (error != 0) {
		cerr << "TEXTURE ERROR: " << error << ": " << lodepng_error_text(error) << endl;
		cerr << "File was : " << fileName << endl;
		return 0;
	}

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texId;
}

void GraphicsUtils::printError(const char* message) {
	int error;
	if ((error = glGetError()) != GL_NO_ERROR) {
		cerr << "error: " << message << ", code: " << hex << error << endl;
	}
}