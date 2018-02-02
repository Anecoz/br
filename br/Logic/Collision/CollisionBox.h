#pragma once

#include <glm\glm.hpp>

using namespace glm;

class CollisionBox
{
public:
	CollisionBox();
	CollisionBox(float x, float y, float w, float h, const vec2& vel);
	~CollisionBox() = default;

	float x;
	float y;
	float w;
	float h;
	vec2 vel;
};

