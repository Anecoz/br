#pragma once

#include "../Player.h"
#include "../Level.h"

class CollisionHandler
{
public:
	CollisionHandler() = delete;
	~CollisionHandler() = delete;

	static bool checkPlayerCollision(Player* player, Level* level);
};

