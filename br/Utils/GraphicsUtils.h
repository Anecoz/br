#pragma once
#include <GL\glew.h>
#include <vector>
#include <iostream>

#include "../Graphics/Lowlevel/IndexedVertexArray.h"
#include "../LodePng/lodepng.h"

using namespace std;

class GraphicsUtils {

public:
	static IndexedVertexArray* createSimpleQuad();
	static GLuint loadPNGToTexture(const char* fileName, unsigned& width, unsigned& height);
};
