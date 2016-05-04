#pragma once
#include "Ammunition.h"
#include <glm\glm.hpp>

using namespace glm;

class Bullet : public Ammunition
{
public:
	Bullet(vec2 position, vec2 velocity, int damage, int uniqueId);
	~Bullet() = default;
};

