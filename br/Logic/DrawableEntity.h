#pragma once

#include "../Graphics/Lowlevel/Texture.h"
#include "../Graphics/Lowlevel/IndexedVertexArray.h"
#include <glm\glm.hpp>

using namespace glm;

class DrawableEntity
{
public:
	DrawableEntity(Texture* texture, const vec2& initPos, float layer);
	~DrawableEntity();

	float getWidth() { return width; }
	float getHeight() { return height; }
	vec2& getPosition() { return position; }
	mat4& getRotation() { return rotation; }

	void renderDisplay(mat4& projection);
	virtual void render(mat4& projection);

protected:
	Texture* texture;
	vec2 position;
	mat4 rotation;
	IndexedVertexArray* mesh;
	float width;
	float height;
	float scale;

	void doRender(bool display, mat4& projection);

private:
	void init(float layer, const vec2& initPos);
};

