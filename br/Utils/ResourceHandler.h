#pragma once

#include "../Graphics/Lowlevel/Texture.h"
#include "../Graphics/Lowlevel/IndexedVertexArray.h"

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	static void init();
	static void cleanUp();

	static Texture* playerTexture;
	static IndexedVertexArray* playerQuad; 

	static Texture* sliderTexture;
	static IndexedVertexArray* sliderQuad;

private:
	
};

