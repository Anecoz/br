#pragma once
#include <GL\glew.h>
#include <vector>
#include <iostream>

#include "../Graphics/Lowlevel/IndexedVertexArray.h"
#include "../LodePng/lodepng.h"
#include "../Graphics/Lowlevel/DynamicLevelVao.h"

using namespace std;

class GraphicsUtils {

public:
	static IndexedVertexArray* createModelQuad(float width, float height, float layer);
	static DynamicLevelVao* createLevelQuad();
	static IndexedVertexArray* createSimpleQuad();
	static GLuint loadPNGToTexture(const char* fileName, unsigned& width, unsigned& height);
	static void printError(const char* message);
};
