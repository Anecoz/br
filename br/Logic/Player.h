#pragma once

#include "DrawableEntity.h"
#include "../Utils/ResourceHandler.h"
#include "Level.h"
#include <glm\glm.hpp>

using namespace glm;

class Player : public DrawableEntity
{
public:
	Player();
	~Player();

	void update(Level* level, mat4& proj);
	float getSpeed() { return SPEED; }
	vec2& getForward() { return forward; }

private:
	static const float SPEED;
	int health = 100;
	vec2 forward;
	bool running = false;

	void updateMovement(Level* level);
	void updateForward(mat4& proj);
	bool isDead();
	void checkRunningStatus();

	bool anyRunningKeysDown();
	bool noRunningKeysDown();

};

