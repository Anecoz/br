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
	static Texture* assaultRifleTexture;
	static Texture* assaultRifleDisplayTexture;
	static Texture* bulletTexture;

	static IndexedVertexArray* playerQuad;
	static IndexedVertexArray* assaultRifleQuad;
	static IndexedVertexArray* bulletQuad;

private:
	
};

