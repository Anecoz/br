#pragma once

#include "../Graphics/Lowlevel/Texture.h"
#include "../Graphics/Lowlevel/IndexedVertexArray.h"

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	static void init();

	static Texture* playerTexture;
	static IndexedVertexArray* playerQuad;

private:
	
};

