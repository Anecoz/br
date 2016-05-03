#include "CollisionHandler.h"
#include <glm\glm.hpp>

using namespace glm;

bool CollisionHandler::checkPlayerCollision(Player* player, Level* level) {
	vec2 playerPos = player->getPosition();
	float w = player->getWidth()/2.0f;
	float h = player->getHeight()/2.0f;
	playerPos.x = playerPos.x + w / 2.0f;
	playerPos.y = playerPos.y + h / 2.0f;

	if (level->getIsCollAt((int)playerPos.x, (int)playerPos.y)) {
		return true;
	}
	else if (level->getIsCollAt((int)(playerPos.x + w), (int)playerPos.y)) {
		return true;
	}
	else if (level->getIsCollAt((int)playerPos.x, (int)(playerPos.y + h))) {
		return true;
	}
	else if (level->getIsCollAt((int)(playerPos.x + w), (int)(playerPos.y + h))) {
		return true;
	}
	else
		return false;
}
