#pragma once

#include "../Graphics/Lowlevel/Texture.h"
#include "../Graphics/Lowlevel/IndexedVertexArray.h"
#include <glm\glm.hpp>

using namespace glm;

class DrawableEntity
{
public:
	DrawableEntity(Texture* texture, vec2& initPos, float layer);
	~DrawableEntity();

protected:
	Texture* texture;
	vec2 position;
	mat4 rotation;
	IndexedVertexArray* mesh;
	float width;
	float height;
	float scale;

private:
	void init(float layer, vec2& initPos);
};

