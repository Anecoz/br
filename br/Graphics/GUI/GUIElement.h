#pragma once
#include "../../Utils/GraphicsUtils.h"
#include "../Lowlevel/Texture.h"
#include "../Lowlevel/IndexedVertexArray.h"
#include <glm\glm.hpp>

using namespace glm;

class GUIElement
{
public:
	GUIElement(Texture* texture, IndexedVertexArray* mesh, vec2 position);
	~GUIElement();

	void render();

protected:
	vec2 position;
	Texture* texture;

private:
	IndexedVertexArray* mesh;
};