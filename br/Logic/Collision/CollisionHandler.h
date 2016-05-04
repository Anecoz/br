#pragma once

#include "../Player.h"
#include "../Level.h"
#include "CollisionBox.h"

class CollisionHandler
{
public:
	CollisionHandler() = delete;
	~CollisionHandler() = delete;

	static bool checkPlayerCollision(Player* player, Level* level);
	static float sweptAABBCollision(const CollisionBox& moving, const CollisionBox& b2);
};

